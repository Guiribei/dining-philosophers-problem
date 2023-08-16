<h1 align="center">
	Philosophers
</h1>

<p align="center">
    <img src="https://github.com/guiribei/guiribei/blob/main/42_badges/philosopherse.png" />
</p>

## Summary
> <i>The dining philosophers problem is a classic synchronization problem where multiple philosophers sit around a table with a bowl of spaghetti in the center. Each philosopher has a fork between themselves and the adjacent philosopher. A philosopher can only eat when they have both the left and right forks. They can either think, sleep, or eat at any given time.</i>

## Description



The challenge is to ensure that all philosophers get a fair chance to eat without causing deadlocks or resource starvation.

## Compilation

1. Clone the repository:

```bash
git clone https://github.com/Guiribei/dining-philosophers-problem.git
```

2. Change to the repository directory:

```bash
cd dining-philosophers-problem
```

3. Compile the project using the provided Makefile:

```bash
make
```

## Usage

#### The program takes 4 or 5 arguments:

- The number of philosophers (and forks).
- The time in milliseconds for a philosopher to die if they haven't started eating.
- The time in milliseconds for a philosopher to eat.
- The time in milliseconds for a philosopher to sleep.
- (Optional) The number of times each philosopher must eat before the simulation ends.

#### Run the program as follows:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_to_eat]
```
#### Example:

```bash
./philo 5 800 200 200 10
```

This example will run the simulation with 5 philosophers, each having 800 ms to eat before they die. They will take 200 ms to eat, 200 ms to sleep, and must eat 10 times each before the simulation ends.
