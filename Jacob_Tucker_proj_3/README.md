CS482 Artificial Intelligence  
Project 3  
Jacob Tucker  
12/5/2021  

Task:  Implement a reinforcement learning algorithm given a python program.  
  
Dependencies: openAI gym, pyglet, numpy, ffmpeg(for visual rendering).  
  
cart.py implements an algorithm to solve the task of balancing a beam on top of a cart. The cart can move left or right in order to keep the beam balanced for at least 200 ticks. Training runs 50,001 episodes with a learning rate of 0.05 and a discount of 0.99.  
  
To run training, use  

    python3 cart.py --train  
    
This will take a while to run. Once it is complete, a cartpole.npy file will be generated for testing.  
To run the test use  

    python3 cart.py --test --model cartpole.npy  
    
This will show the program using the trained model to complete the task of balancing the beam for at least 200 ticks.  
  
  
car.py uses a similar learning algorithm to accomplish the task of moving a car up a hill to a flag. The car starts in a valley and can move left, right or null. For this training model, the learning rate is set to 0.7 with a discount of 0.95  

To run training, use  
    
    python3 car.py --train  
    
Similar to cart.py, this will generate a car.npy model for testing.  
To test, use  
    
    python3 car.py --test --model car.npy  
    
This will render the visual of the car attempting to accomplish the task of reaching the flag based on the trained model.  
