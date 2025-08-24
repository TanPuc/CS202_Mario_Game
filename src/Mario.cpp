#include "Mario.h"

Mario::Mario(Vector2 position)
    : Entity(position, Vector2({MARIO_WIDTH, MARIO_HEIGHT})),
      form(SMALL),
      hurtBuffer(0.0f),
      lives(3), coins(0), score(0)
{
    rect = {position.x, position.y, MARIO_WIDTH, MARIO_HEIGHT};
    sprite = std::make_unique<MarioSprite>();
    currentState = std::make_unique<IdleState>();
}

Mario::Mario(Vector2 position, std::function<void()> onDeathAction)
    : Entity(position, Vector2({MARIO_WIDTH, MARIO_HEIGHT})),
      form(SMALL),
      hurtBuffer(0.0f),
      lives(3),
      coins(0),
      score(0),
      onDeath(std::move(onDeathAction))
{
    rect = {position.x, position.y, MARIO_WIDTH, MARIO_HEIGHT};
    sprite = std::make_unique<MarioSprite>();
    currentState = std::make_unique<IdleState>();
}

void Mario::Die()
{
    Shrink();
    lives--;
    currentState = std::make_unique<DeadState>();
    // Animation
    velocity.y = -500.0f;
}

void Mario::Grow()
{
    if (form != SMALL)
        return;
    form = BIG;
    rect.height = MARIO_HEIGHT * 2.0f;
    sprite->SwitchForm(form);
}

void Mario::ChangeToFire()
{
    if (form != BIG)
        return;
    form = FIRE;
    rect.height = MARIO_HEIGHT * 2.0f;
    sprite->SwitchForm(form);
}

void Mario::ChangeToSuper()
{
    if (form != BIG)
        return;
    form = SUPER;
    rect.height = MARIO_HEIGHT * 2.0f;
    sprite->SwitchForm(form);
}

void Mario::Shrink()
{
    if (form == SMALL)
        return;
    form = SMALL;
    rect.height = MARIO_HEIGHT;
    sprite->SwitchForm(form);
}

void Mario::ChangeForm()
{
    if (IsKeyPressed(KEY_F))
    {
        if (form == SMALL)
        {
            form = BIG;
            rect.height = MARIO_HEIGHT * 2.0f;
        }
        else if (form == BIG)
        {
            form = FIRE;
            rect.height = MARIO_HEIGHT * 2.0f;
        }
        else if (form == FIRE)
        {
            form = SMALL;
            rect.width = MARIO_WIDTH;
            rect.height = MARIO_HEIGHT;
        }
        std::cout << "Mario changed form to: " << form << std::endl;
    }
    if (IsKeyPressed(KEY_R))
    {
        form = SMALL;
        rect.width = MARIO_WIDTH;
        rect.height = MARIO_HEIGHT;
    }

    sprite->SwitchForm(form);
}

void Mario::HandleInput()
{
    std::unique_ptr<MarioState> newState = currentState->HandleInput(*this, *sprite);
    if (newState != nullptr)
    {
        currentState = std::move(newState);
    }
}

void Mario::Draw()
{
    DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, RED);
    currentState->Draw(*this, *sprite);
}

void Mario::Hurt()
{
    if (hurtBuffer > 0) // Invisibility frame active
        return;
    hurtBuffer = HURT_BUFFER_THRESHOLD;
    if (form == SMALL)
        Die();
}

bool Mario::IsHurt() const
{
    if (hurtBuffer > 0.0f)
    {
        return true;
    }
    return false;
}

void Mario::Update(Level &level)
{
    float dt = GetFrameTime();
    std::unique_ptr<MarioState> newState = currentState->Update(*this, *sprite);
    if (newState != nullptr)
    {
        currentState = std::move(newState);
    }

    if (hurtBuffer > 0.0f)
    {
        hurtBuffer -= GetFrameTime();
    }
    else
    {
        hurtBuffer = 0.0f;
    }

    ApplyGravity(velocity, GRAVITY);

    if (currentState->GetType() != STATE_DEAD) // Mario is not dead
    {
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
    else
    {
        position.y += velocity.y * dt;
        rect.y = position.y;

        if (position.y > HEIGHT_BOUNDARY)
        {
            std::cout << "Mario fell out of the world." << std::endl;
            if (onDeath != nullptr)
                onDeath();
        }
    }
}

void Mario::ResolveCollision(Level &level)
{
    collision.CheckCollision(position, rect, velocity, level);
    collision.ResolveCollision(position, rect, velocity, level);
}

DIRECTION Mario::GetDirection() const
{
    return direction;
}

MARIO_FORM Mario::GetForm() const
{
    return form;
}

Vector2 Mario::GetPosition() const
{
    return position;
}

void Mario::SetPosition(Vector2 newPosition)
{
    position = newPosition;
    rect.x = position.x;
    rect.y = position.y;
}

void Mario::SetOnDeathAction(std::function<void()> action)
{
    onDeath = std::move(action);
}