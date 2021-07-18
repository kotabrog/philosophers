# philosophers

## Overview

To practice the threading process, I had a philosopher over for dinner.

## Usage

```
git clone https://github.com/kotabrog/philosophers.git
cd philosophers
make
```

For example, you can run the following to see two philosophers having a meal.

```
./philo 2 20 5 4 3
```

## Features

This program is designed for the following situations.

- The philosophers sit around a round table, in the middle of which is spaghetti.
- Philosophers go to sleep right after eating, start thinking when they finish sleeping, and eat when they have a chance to eat.
- Philosophers starve to death if they can't eat for a while.
- A philosopher can't eat spaghetti without a fork in each hand.
- There are the same number of philosophers and forks, with a fork between each philosopher.

The following can be specified as program arguments.
- number of philosophers
- time to die
- time to eat
- time to sleep
- number of times each philosopher must eat (optional)

For example, in the previous example, there are two philosophers, the philosopher dies if he cannot eat for 20 ms, eating takes 5 ms, he sleeps for 4 ms after eating, and the simulation ends when he has eaten three times.

If you don't give the last argument, the simulation won't end until someone dies.

The philosopher's status is displayed, for example, as follows.

```
[timestamp in ms] [Philosopher's number] has taken a fork
```

We use mutex to achieve parallel processing.

## Author

[twiter](https://twitter.com/Kotabrog)

## Licence

[MIT](https://github.com/kotabrog/philosophers/blob/main/LICENSE)
