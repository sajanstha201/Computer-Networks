import numpy as np
import random

# Parameters for the environment
total_bandwidth = 100
num_slices = 3
slice_bandwidths = [40, 30, 20]  # QoS requirements for slices 1, 2, and 3 respectively
slice_priorities = [3, 2, 1]  # Priority levels for each slice

# Q-learning parameters
alpha = 0.1  # Learning rate
gamma = 0.9  # Discount factor
epsilon = 0.1  # Exploration rate
num_episodes = 1000

# Initialize Q-table
Q = np.zeros((total_bandwidth + 1, 2 ** num_slices))

# Reward function
def calculate_reward(allocation):
    reward = 0
    for i in range(num_slices):
        if allocation[i] >= slice_bandwidths[i]:  # If allocation meets or exceeds QoS requirement
            reward += slice_priorities[i]  # Reward based on priority
        else:
            reward -= (slice_bandwidths[i] - allocation[i])  # Penalty for unmet QoS requirements
    return reward

# Environment step
def step(state, action):
    allocation = np.zeros(num_slices)
    remaining_bandwidth = state
    
    for i in range(num_slices):
        if action & (1 << i):
            allocation[i] = min(slice_bandwidths[i], remaining_bandwidth)
            remaining_bandwidth -= allocation[i]
    
    reward = calculate_reward(allocation)
    new_state = int(max(0, remaining_bandwidth))  # Ensure new_state is within bounds and an integer
    
    return new_state, reward, allocation

# Q-learning algorithm
for episode in range(num_episodes):
    state = total_bandwidth
    
    for _ in range(num_slices):
        if random.uniform(0, 1) < epsilon:
            action = random.randint(0, 2 ** num_slices - 1)
        else:
            action = np.argmax(Q[state])
        
        new_state, reward, allocation = step(state, action)
        
        # Restrict new_state to within the Q-table bounds
        new_state = min(max(0, new_state), total_bandwidth)  # Ensure new_state is within [0, total_bandwidth]
        
        best_next_action = np.argmax(Q[new_state])
        Q[state, action] = Q[state, action] + alpha * (reward + gamma * Q[new_state, best_next_action] - Q[state, action])
        
        state = new_state

# Testing the trained model
state = total_bandwidth
action = np.argmax(Q[state])
_, _, final_allocation = step(state, action)

print("Final Channel Allocation for Each Slice (in units):")
for i in range(num_slices):
    print(f"Slice {i+1}: {int(final_allocation[i])} units")
print(f"Remaining Bandwidth: {int(state - sum(final_allocation))} units")
