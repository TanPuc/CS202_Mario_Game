#include "MarioState.h"

// ---------------- IdleState ----------------
std::unique_ptr<MarioState> IdleState::HandleInput(Entity &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;                           // Set direction to LEFT when moving left
        ClampVelocity(player.velocity);                    // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING); // Switch to walking state
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;                          // Set direction to RIGHT when moving right
        ClampVelocity(player.velocity);                    // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING); // Switch to walking state
        return std::make_unique<WalkingState>();
    }
    else
    {
        if (player.velocity.x < 0)
        {
            player.velocity.x += (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x > 0)
            {
                player.velocity.x = 0;                          // Stop if deceleration makes velocity negative
                sprite.SwitchAnimation(STATE_IDLE); // Switch to walking state
                return std::make_unique<IdleState>();
            }
        }
        else if (player.velocity.x > 0)
        {
            player.velocity.x -= (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x < 0)
            {
                player.velocity.x = 0;                          // Stop if deceleration makes velocity negative
                sprite.SwitchAnimation(STATE_IDLE); // Switch to walking state
                return std::make_unique<IdleState>();
            }
        }
        ClampVelocity(player.velocity); // Ensure velocity is clamped
    }
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player.velocity.y == 0) // Only jump if on the ground
    {
        player.velocity.y = -JUMP_FORCE; // Apply jump force
        sprite.SwitchAnimation(STATE_JUMPING); // Switch to walking state
        return std::make_unique<JumpingState>();
    }
    return nullptr; // Stay in Idle state if no input
}

std::unique_ptr<MarioState> IdleState::Update(Entity &player)
{
    std::cout << "Current MarioState: Idle" << std::endl;
    return nullptr;
}

void IdleState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}

// ---------------- WalkingState ----------------
std::unique_ptr<MarioState> WalkingState::HandleInput(Entity &player)
{
    float deltaTime = GetFrameTime();
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;                           // Set direction to LEFT when moving left
        ClampVelocity(player.velocity);                    // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING); // Switch to walking state
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;       // Set direction to RIGHT when moving right
        ClampVelocity(player.velocity); // Ensure velocity is clamped

        player.marioSprite.SwitchAnimation(STATE_WALKING); // Switch to walking state
        return std::make_unique<WalkingState>();
    }
    else
    {
        if (player.velocity.x < 0)
        {
            player.velocity.x += (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x > 0)
            {
                player.velocity.x = 0;                          // Stop if deceleration makes velocity negative
                player.marioSprite.SwitchAnimation(STATE_IDLE); // Switch to walking state
                return std::make_unique<IdleState>();
            }
        }
        else if (player.velocity.x > 0)
        {
            player.velocity.x -= (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x < 0)
            {
                player.velocity.x = 0;                          // Stop if deceleration makes velocity negative
                player.marioSprite.SwitchAnimation(STATE_IDLE); // Switch to walking state
                return std::make_unique<IdleState>();
            }
        }
        ClampVelocity(player.velocity); // Ensure velocity is clamped
    }
    if (IsKeyPressed(KEY_SPACE) && player.velocity.y == 0) // Only jump if on the ground
    {
        player.velocity.y = -JUMP_FORCE;                   // Apply jump force
        player.marioSprite.SwitchAnimation(STATE_JUMPING); // Switch to jumping state
        return std::make_unique<JumpingState>();
    }
    return std::make_unique<WalkingState>(); // Stay in Walking state if no input
}

std::unique_ptr<MarioState> WalkingState::Update(Entity &player)
{
    std::cout << "Current MarioState: Walking" << std::endl;
    return nullptr;
}

void WalkingState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}

// ---------------- JumpingState ----------------
std::unique_ptr<MarioState> JumpingState::HandleInput(Entity &player)
{
    float deltaTime = GetFrameTime();
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;        // Set direction to LEFT when moving left
        ClampVelocity(player.velocity); // Ensure velocity is clamped
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;       // Set direction to RIGHT when moving right
        ClampVelocity(player.velocity); // Ensure velocity is clamped
        return std::make_unique<WalkingState>();
    }
    else
    {
        if (player.velocity.x < 0)
        {
            player.velocity.x += (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x > 0)
            {
                player.velocity.x = 0; // Stop if deceleration makes velocity negative
                return std::make_unique<IdleState>();
            }
        }
        else if (player.velocity.x > 0)
        {
            player.velocity.x -= (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x < 0)
            {
                player.velocity.x = 0; // Stop if deceleration makes velocity negative
                return std::make_unique<IdleState>();
            }
        }
        ClampVelocity(player.velocity); // Ensure velocity is clamped
    }
    return nullptr; // Stay in Jumping state if no input
}

std::unique_ptr<MarioState> JumpingState::Update(Entity &player)
{
    std::cout << "Current MarioState: Jumping" << std::endl;
    return nullptr;
}

void JumpingState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}
