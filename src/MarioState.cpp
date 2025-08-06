#include "MarioState.h"

// ---------------- IdleState ----------------
std::unique_ptr<MarioState> IdleState::HandleInput(Entity &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player.velocity.y == 0) // Only jump if on the ground
    {
        player.velocity.y = -JUMP_FORCE; // Apply jump force
        return std::make_unique<JumpingState>();
    }

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
    return nullptr; // Stay in Idle state if no input
}

std::unique_ptr<MarioState> IdleState::Update(Entity &player, Sprite &sprite)
{

    std::cout << "Current MarioState: Idle" << std::endl;
    
    if (player.velocity.x == 0 && player.velocity.y == 0) // If velocity is zero, stay in Idle state
    {
        sprite.SwitchAnimation(STATE_IDLE); // Ensure Idle animation is set
    }
    else if (player.velocity.y != 0)
    {
        sprite.SwitchAnimation(STATE_JUMPING);   // Switch to Jumping animation if moving up
        return std::make_unique<JumpingState>(); // Transition to Jumping state if moving up
    }
    else
    {
        sprite.SwitchAnimation(STATE_WALKING); // If there's any movement, switch to Walking state
        return std::make_unique<WalkingState>();
    }
    return nullptr; // No state change in Idle state
}

void IdleState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}

// ---------------- WalkingState ----------------
std::unique_ptr<MarioState> WalkingState::HandleInput(Entity &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_SPACE) && player.velocity.y == 0) // Only jump if on the ground
    {
        player.velocity.y = -JUMP_FORCE; // Apply jump force
        return std::make_unique<JumpingState>();
    }
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
    return std::make_unique<WalkingState>(); // Stay in Walking state if no input
}

std::unique_ptr<MarioState> WalkingState::Update(Entity &player, Sprite &sprite)
{
    std::cout << "Current MarioState: Walking" << std::endl;
    if (player.velocity.y != 0)
    {
        sprite.SwitchAnimation(STATE_JUMPING);   // Switch to Jumping animation if moving up
        return std::make_unique<JumpingState>(); // Transition to Jumping state if moving up
    }
    if (player.velocity.x != 0 || player.velocity.y == 0)
    {
        sprite.SwitchAnimation(STATE_WALKING);   // Switch to Idle animation if no horizontal movement
        return std::make_unique<WalkingState>(); // Transition to Walking state if there's horizontal movement
    }
    return nullptr;
}

void WalkingState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}

// ---------------- JumpingState ----------------
std::unique_ptr<MarioState> JumpingState::HandleInput(Entity &player, Sprite &sprite)
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
            }
        }
        else if (player.velocity.x > 0)
        {
            player.velocity.x -= (MAX_VELOCITY * DECELERATION * deltaTime);
            if (player.velocity.x < 0)
            {
                player.velocity.x = 0; // Stop if deceleration makes velocity negative
            }
        }
        ClampVelocity(player.velocity); // Ensure velocity is clamped
    }
    return nullptr; // Stay in Jumping state if no input
}

std::unique_ptr<MarioState> JumpingState::Update(Entity &player, Sprite &sprite)
{
    std::cout << "Current MarioState: Jumping" << std::endl;
    if (player.velocity.y == 0) // If Mario is on the ground
    {
        sprite.SwitchAnimation(STATE_IDLE);   // Switch to Idle animation if on the ground
        return std::make_unique<IdleState>(); // Transition to Idle state
    }
    sprite.SwitchAnimation(STATE_JUMPING); // Ensure Jumping animation is set
    return nullptr; // Stay in Jumping state
}

void JumpingState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}