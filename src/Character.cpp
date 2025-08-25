#include "CharacterState/CharacterState.h"
#include "CharacterState/IdleState.h"
#include "CharacterState/DeadState.h"
#include "CharacterState/SlidingState.h"
#include "CharacterState/ThrowingState.h"
#include "CharacterState/WalkingState.h"

Character::Character(Vector2 position)
    : Entity(position, Vector2({CHARACTER_WIDTH, CHARACTER_HEIGHT})),
      form(SMALL),
      hurtBuffer(0.0f),
      lives(3), coins(0), score(0)
{
    rect = {position.x, position.y, CHARACTER_WIDTH, CHARACTER_HEIGHT};
    sprite = std::make_unique<MarioSprite>();
    throwingSprite = std::make_unique<ThrowingSprite>();
    currentState = std::make_unique<IdleState>();
}

Character::Character(Vector2 position, std::function<void()> onDeathAction)
    : Entity(position, Vector2({CHARACTER_WIDTH, CHARACTER_HEIGHT})),
      form(SMALL),
      hurtBuffer(0.0f),
      lives(3),
      coins(0),
      score(0),
      onDeath(std::move(onDeathAction))
{
    rect = {position.x, position.y, CHARACTER_WIDTH, CHARACTER_HEIGHT};
    sprite = std::make_unique<MarioSprite>();
    throwingSprite = std::make_unique<ThrowingSprite>();
    currentState = std::make_unique<IdleState>();
}

Character::Character(CHARACTER character, Vector2 position, std::function<void()> onDeathAction)
    : Entity(position, Vector2({CHARACTER_WIDTH, CHARACTER_HEIGHT})),
      form(SMALL),
      hurtBuffer(0.0f),
      lives(3),
      coins(0),
      score(0),
      onDeath(std::move(onDeathAction)),
      character(character)
{
    rect = {position.x, position.y, CHARACTER_WIDTH, CHARACTER_HEIGHT};
    if (character == MARIO)
    {
        sprite = std::make_unique<MarioSprite>();
    }
    else
    {
        sprite = std::make_unique<LuigiSprite>();
    }
    throwingSprite = std::make_unique<ThrowingSprite>();
    currentState = std::make_unique<IdleState>();
}

void Character::Die()
{
    Shrink();
    lives--;
    currentState = std::make_unique<DeadState>();
    // Animation
    velocity.y = -500.0f;
}

void Character::Grow()
{
    form = BIG;
    rect.height = CHARACTER_HEIGHT * 2.0f;
    sprite->SwitchForm(form);
}

void Character::ChangeToFire()
{
    form = FIRE;
    rect.height = CHARACTER_HEIGHT * 2.0f;
    sprite->SwitchForm(form);
}

void Character::ChangeToSuper()
{
    form = SUPER;
    rect.height = CHARACTER_HEIGHT * 2.0f;
    sprite->SwitchForm(form);
}

void Character::Shrink()
{
    form = SMALL;
    rect.height = CHARACTER_HEIGHT;
    sprite->SwitchForm(form);
}

void Character::ChangeForm(CHARACTER_FORM newForm)
{
    if (form == newForm)
        return;

    std::cout << "Form change initiated from " << form << " to " << newForm << std::endl;

    isTransforming = true;
    transformTimer = 1.0f; // 5 seconds
    previousForm = form;
    targetForm = newForm;
}

void Character::ChangeForm()
{
    if (IsKeyPressed(KEY_F))
    {
        if (form == SMALL)
        {
            form = BIG;
            rect.height = CHARACTER_HEIGHT * 2.0f;
        }
        else if (form == BIG)
        {
            form = FIRE;
            rect.height = CHARACTER_HEIGHT * 2.0f;
        }
        else if (form == FIRE)
        {
            form = SMALL;
            rect.width = CHARACTER_WIDTH;
            rect.height = CHARACTER_HEIGHT;
        }
        std::cout << "Character changed form to: " << form << std::endl;
    }
    if (IsKeyPressed(KEY_R))
    {
        form = SMALL;
        rect.width = CHARACTER_WIDTH;
        rect.height = CHARACTER_HEIGHT;
    }

    sprite->SwitchForm(form);
}

void Character::Slide(Vector2 contactPoint) // Contact Point is a x, y coordinate according to the level grid
{
    // Start sliding
    currentState = std::make_unique<SlidingState>();
    // Snap to Ox grid
    contactPoint.x = static_cast<int>(contactPoint.x) / (TILE_SIZE * SCALE) * (TILE_SIZE * SCALE);
    velocity = {0, 0};
}

void Character::ShootFireBall()
{
    isThrowing = true;
    throwTimer = THROWING_FRAME_THRESHOLD;
}

void Character::HandleInput()
{
    std::unique_ptr<CharacterState> newState = currentState->HandleInput(*this, *sprite);
    if (newState != nullptr)
    {
        currentState = std::move(newState);
    }
}

void Character::Draw()
{
    DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);
    if (isThrowing)
        throwingSprite->Draw(*this);
    else
        currentState->Draw(*this, *sprite);
}

void Character::Hurt()
{
    if (hurtBuffer > 0) // Invisibility frame active
        return;
    hurtBuffer = HURT_BUFFER_THRESHOLD;
    if (form == SMALL)
        Die();
}

bool Character::IsHurt() const
{
    if (hurtBuffer > 0.0f)
    {
        return true;
    }
    return false;
}

void Character::ChangeToTargetForm(CHARACTER_FORM targetForm)
{
    switch (targetForm)
    {
    case SMALL:
        Shrink();
        break;
    case BIG:
        Grow();
        break;
    case FIRE:
        ChangeToFire();
        break;
    }
}

void Character::Update(Level &level)
{
    float dt = GetFrameTime();

    // Prevent animation from being interrupted

    if (playWinAnimation)
    {
        if (!onGround)
        {
            CheckOnGround(level);
            sprite->SwitchAnimation(STATE_SLIDING);
            std::cout << "Is not on ground\n";
            position.y += FLAG_SPEED * dt;
            rect.y = position.y;
        }
        else
        {
            std::cout << "Is on ground\n";
            if (walkTime > 0)
            {
                position.x += 100.0f * dt;
                rect.x = position.x;
                sprite->SwitchAnimation(STATE_WALKING);
            }

            timeToCastle -= dt;
            walkTime -= dt;

            if (timeToCastle <= 0)
            {
                playWinAnimation = true;
                std::cout << "Character reached the castle." << std::endl;
                if (onChangeScene != nullptr)
                    onChangeScene();
            }
        }

        return;
    }
    else if (isThrowing)
    {
        throwTimer--;
        if (throwTimer <= 0)
        {
            isThrowing = false;
            // std::cout << "Finished throwing animation\n";
        }
    }
    else if (isTransforming)
    {
        transformTimer -= dt; // float time countdown

        // Handle frame toggling
        frameIndex++;
        if (frameIndex >= FRAME_INDEX_THRESHOLD) // e.g. 10 frames
        {
            frameIndex = 0;
            // Toggle between old and new form visually
            showingTarget = !showingTarget;
            // std::cout << "Toggling form display: " << (showingTarget ? "Target Form" : "Previous Form") << std::endl;
            if (showingTarget)
                ChangeToTargetForm(targetForm);
            else
                ChangeToTargetForm(previousForm);
        }

        // End transformation
        if (transformTimer <= 0.0f)
        {
            // std::cout << "Form change completed: " << previousForm << " -> " << targetForm << std::endl;
            isTransforming = false;
            form = targetForm;
            ChangeToTargetForm(form);

            // Reset
            transformTimer = 0.0f;
            frameIndex = 0;
            showingTarget = false;
        }
        return;
    }

    HandleInput();

    std::unique_ptr<CharacterState> newState = currentState->Update(*this, *sprite);
    if (newState != nullptr)
    {
        currentState = std::move(newState);
    }

    switch (currentState->GetType())
    {
    case STATE_DEAD:
    {
        ApplyGravity(velocity, GRAVITY);

        position.y += velocity.y * dt;
        rect.y = position.y;

        if (position.y > HEIGHT_BOUNDARY)
        {
            std::cout << "Character fell out of the world." << std::endl;
            if (onDeath != nullptr)
                onDeath();
        }
        break;
    }
    case STATE_SLIDING:
    {
        if (collision.IsCollideWithLevel(position, rect, velocity, level))
        {
            // Handle collision with ground
            currentState = std::make_unique<IdleState>();
        }
        ResolveCollision(level);

        position.y += velocity.y * dt;
        rect.y = position.y;
        break;
    }
    default:
    {
        ApplyGravity(velocity, GRAVITY);

        if (position.x < 0)
        {
            position.x = 0;
            velocity.x = 0;
        }

        ResolveCollision(level);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        rect.x = position.x;
        rect.y = position.y;
    }
    }

    // If transformation animation is on-going, don't update the position
    // Checking for hurt invincibility
    // if (hurtBuffer > 0.0f)
    //     hurtBuffer -= GetFrameTime();
    // else
    //     hurtBuffer = 0.0f;

    // if (isTransforming)
    //     return;
}

void Character::ResolveCollision(Level &level)
{
    // collision.CheckCollision(position, rect, velocity, level);
    // collision.ResolveCollision(position, rect, velocity, level);
    collision.PlayerVsLevel(position, rect, velocity, level);
}

DIRECTION Character::GetDirection() const
{
    return direction;
}

CHARACTER_FORM Character::GetForm() const
{
    return form;
}

Vector2 Character::GetPosition() const
{
    return position;
}

void Character::SetPosition(Vector2 newPosition)
{
    position = newPosition;
    rect.x = position.x;
    rect.y = position.y;
}

void Character::SetOnDeathAction(std::function<void()> action)
{
    onDeath = std::move(action);
}

void Character::PlayWinAnimation()
{
    if (!playWinAnimation)
    {
        playWinAnimation = true;
        velocity = {0.0f, 0.0f};
    }
}

void Character::CheckOnGround(Level &level)
{
    // Check if the character is on the ground
    onGround = collision.IsCollideWithLevelVertically(position, rect, velocity, level);
}