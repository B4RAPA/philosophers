# 42_philosophers
Philosophers - Project at 42 school (42 Wolfsburg)

<h1 align="center">
	🍝 Philosophers
</h1>

<p align="center">
	<b><i>Dining Philosophers Problem – Multithreading & Synchronization in C</i></b><br>
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-What-I-Learned">What I Learned</a>
</h3>

---

## 💡 About the project

> _Philosophers is a classic computer science project that explores the challenges of concurrency, resource sharing, and process synchronization. The task is to implement a simulation of the Dining Philosophers Problem using multithreading in C, managing access to shared resources (forks) and preventing deadlocks and race conditions. The project deepens understanding of thread management, mutexes, and the complexities of concurrent programming._

## 🛠️ Usage

### Requirements

The project is written in C and requires the **`gcc` compiler** and standard **POSIX threads library (`-lpthread`)** to run.

### Instructions

**1. Compiling the project**

To compile, navigate to the project directory and run:

```shell
$ make
```

**2. Running the program**

To start the simulation, run:

```shell
$ ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
```

**Example:**

```shell
$ ./philosophers 5 800 200 200
```

## 📚 What I Learned

- Multithreading and thread management in C
- Mutexes and synchronization primitives
- Avoiding deadlocks and race conditions
- Simulating concurrent systems
- Debugging concurrent applications
