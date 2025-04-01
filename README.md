# Title #

## Student's Info ##

**Name:** Nguyen Thanh Duong

**Class:** K69I-CS5

**Student's ID:** 24021441

## About the game : Last Stand ##

Last Stand is a top-down shooter game which takes place in the post apocalypse world where player survive through continuous waves of zombies and other infected beasts. 
The game is in its beta an currently only has Endless Mode. Campaign Mode are expected to come in future updates.

### Features ###

#### Movements and Camera ####

The game provides simple and reactive movement mechanism. The camera follows player around and has some mild shaking effect for realism.

The camera shake is implemented using Perlin Noise, an algorithm which combines randomness with smoothness, therefore providing the desired 
result despite being easy to implement.

#### Entity Component System (ECS) #### 

Instead of Object Oriented Programming (OOP), this game is built on ECS. The system treats each object as Game Object which holds multiple 
components. Each component has its own functionality, which when combined shape the object's behaviour.

For example, the Transform component handles movement logic, while BoxCollider handles physical interaction, this case being collision, between 
objects, etc. An object can have a list of different components to shape its behaviour instead of having to write movement logic in every Player
and Entity class.

GameObject also comes with a handful of method to provide flexibility in shaping different object behaviours.
