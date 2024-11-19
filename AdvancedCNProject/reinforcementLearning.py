import numpy as np
import random

# Define the environment parameters
NUM_SLICES = 3  # Number of network slices
TOTAL_BANDWIDTH = 100  # Total available bandwidth units
QOS_REQUIREMENTS = [40, 30, 20]  # Required bandwidth for each slice

# Q-learning parameters
NUM_EPISODES = 1000  # Number of training episodes
LEARNING_RATE = 0.1  # Learning rate for Q-learning
DISCOUNT_FACTOR = 0.9  # Discount factor for Q-learning
EPSILON = 0.1  # Epsilon for epsilon-greedy policy

# Define states and actions
states = [(i, j, k) for i in range(TOTAL_BANDWIDTH+1) for j in range(TOTAL_BANDWIDTH+1-i) for k in range(TOTAL_BANDWIDTH+1-i-j)]
actions = [-1, 0, 1]  # Possible adjustments for each slice

# Initialize Q-table
q_table = np.zeros((len(states), NUM_SLICES, len(actions)))

def get_state_index(state):
    return states.index(state)

# Define reward function
def get_reward(allocation):
    reward = 0
    for i in range(NUM_SLICES):
        if allocation[i] >= QOS_REQUIREMENTS[i]:
            reward += allocation[i]  # Reward for meeting QoS
        else:
            reward -= (QOS_REQUIREMENTS[i] - allocation[i])  # Penalty for falling short
    return reward

# Select action based on epsilon-greedy policy
def choose_action(state_index, slice_index):
    if random.uniform(0, 1) < EPSILON:
        return random.choice(range(len(actions)))  # Random action (exploration)
    else:
        return np.argmax(q_table[state_index][slice_index])  # Best action (exploitation)

# Simulate environment for a single episode
for episode in range(NUM_EPISODES):
    # Initialize random allocation
    allocation = [QOS_REQUIREMENTS[i] for i in range(NUM_SLICES)]
    state = tuple(allocation)
    state_index = get_state_index(state)
    
    done = False
    while not done:
        # For each slice, choose an action
        for i in range(NUM_SLICES):
            action = choose_action(state_index, i)
            allocation[i] = max(0, allocation[i] + actions[action])  # Update allocation

        # Calculate reward and next state
        reward = get_reward(allocation)
        new_state = tuple(allocation)
        new_state_index = get_state_index(new_state)
        
        # Update Q-value
        for i in range(NUM_SLICES):
            action = choose_action(state_index, i)
            q_table[state_index][i][action] = q_table[state_index][i][action] + LEARNING_RATE * (
                reward + DISCOUNT_FACTOR * np.max(q_table[new_state_index][i]) - q_table[state_index][i][action]
            )
        
        # Move to the new state
        state_index = new_state_index
        
        # Check if we've met the QoS requirements
        if all(allocation[i] >= QOS_REQUIREMENTS[i] for i in range(NUM_SLICES)):
            done = True

# Testing the learned policy
test_allocation = [QOS_REQUIREMENTS[i] for i in range(NUM_SLICES)]
state = tuple(test_allocation)
state_index = get_state_index(state)

for i in range(NUM_SLICES):
    action = np.argmax(q_table[state_index][i])
    test_allocation[i] = max(0, test_allocation[i] + actions[action])

print("Final optimized allocation:", test_allocation)
print("Reward for this allocation:", get_reward(test_allocation))
