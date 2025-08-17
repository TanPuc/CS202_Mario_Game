#include "MarioState.h"

// ---------------- IdleState ----------------
std::unique_ptr<MarioState> IdleState::HandleInput(Entity &player, Sprite &sprite)
{
    float deltaTime = GetFrameTime();

    /// Jumping

    // Count Jump time
    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) // Full Jump
    {
        jump_time++;
        // std::cout << "Jump hold time: " << jump_time << std::endl;
        if (jump_time >= JUMP_TIME_THRESHOLD) // If jump button held for too long,
        {
            player.velocity.y = -JUMP_FORCE; // Apply jump force
            std::cout << "Jump button held too long, staying in Idle state." << std::endl;
            jump_time = 0; // Reset jump time

            sprite.SwitchAnimation(STATE_JUMPING);
            return std::make_unique<JumpingState>();
        }
        else
            return nullptr;
    }

    if (jump_time > 0 && (IsKeyUp(KEY_SPACE) || IsKeyUp(KEY_UP) || IsKeyUp(KEY_W))) // Half Jump
    {
        // std::cout << "Jump button released, applying jump force. " << jump_time << " Jump power: " << -JUMP_FORCE * (HALF + float(0.03f * jump_time)) << std::endl;
        player.velocity.y = -JUMP_FORCE * (HALF + float(0.05f * jump_time)); // Apply half jump force
        jump_time = 0;                                                       // Reset jump time
        sprite.SwitchAnimation(STATE_JUMPING);
        return std::make_unique<JumpingState>();
    }

    /// Walking
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;        // Set direction to LEFT when moving left
        ClampVelocity(player.velocity); // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING);
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;       // Set direction to RIGHT when moving right
        ClampVelocity(player.velocity); // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING);
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

    // std::cout << "Current MarioState: Idle" << std::endl;

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
    /// Jumping

    // Count Jump time
    if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) // Full Jump
    {
        jump_time++;
        // std::cout << "Jump hold time: " << jump_time << std::endl;
        if (jump_time >= JUMP_TIME_THRESHOLD) // If jump button held for too long,
        {
            player.velocity.y = -JUMP_FORCE; // Apply jump force
            std::cout << "Jump button held too long, staying in Idle state." << std::endl;
            jump_time = 0; // Reset jump time
            sprite.SwitchAnimation(STATE_JUMPING);
            return std::make_unique<JumpingState>();
        }
        else
            return nullptr;
    }

    if (jump_time > 0 && (IsKeyUp(KEY_SPACE) || IsKeyUp(KEY_UP) || IsKeyUp(KEY_W))) // Half Jump
    {
        // std::cout << "Jump button released, applying jump force. " << jump_time << " Jump power: " << -JUMP_FORCE * (HALF + float(0.03f * jump_time)) << std::endl;
        player.velocity.y = -JUMP_FORCE * (HALF + float(0.05f * jump_time)); // Apply half jump force
        jump_time = 0;                                                       // Reset jump time
        sprite.SwitchAnimation(STATE_JUMPING);
        return std::make_unique<JumpingState>();
    }

    /// Walking
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        player.velocity.x += (-MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = LEFT;        // Set direction to LEFT when moving left
        ClampVelocity(player.velocity); // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING);
        return std::make_unique<WalkingState>();
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        player.velocity.x += (MAX_VELOCITY * ACCELERATION * deltaTime);
        player.direction = RIGHT;       // Set direction to RIGHT when moving right
        ClampVelocity(player.velocity); // Ensure velocity is clamped
        sprite.SwitchAnimation(STATE_WALKING);
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
    return nullptr; // Stay in Walking state if no input
}

std::unique_ptr<MarioState> WalkingState::Update(Entity &player, Sprite &sprite)
{
    // std::cout << "Current MarioState: Walking" << std::endl;
    if (player.velocity.y != 0) // Switch to Jumping animation if moving up
    {
        sprite.SwitchAnimation(STATE_JUMPING);
        return std::make_unique<JumpingState>();
    }
    if (player.velocity.x != 0 || player.velocity.y == 0) // Switch to Walking animation if no vertical movement
    {
        if ((player.velocity.x < 0 && player.direction == RIGHT) || (player.velocity.x > 0 && player.direction == LEFT))
        {
            sprite.SwitchAnimation(STATE_DECELERATING); // Switch to Decelerating animation if direction is opposite
            return std::make_unique<WalkingState>();    // Stay in Walking state
        }
        else
        {
            sprite.SwitchAnimation(STATE_WALKING);
            return std::make_unique<WalkingState>();
        }
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

    // Walking
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
    // std::cout << "Current MarioState: Jumping" << std::endl;
    if (player.velocity.y == 0) // If Mario is on the ground
    {
        sprite.SwitchAnimation(STATE_IDLE);   // Switch to Idle animation if on the ground
        return std::make_unique<IdleState>(); // Transition to Idle state
    }
    sprite.SwitchAnimation(STATE_JUMPING); // Ensure Jumping animation is set
    return nullptr;                        // Stay in Jumping state
}

void JumpingState::Draw(Entity &player, Sprite &sprite)
{
    sprite.Draw(player);
}