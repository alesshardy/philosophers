# philosophers 🍽️

<div align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Threading-FF6B6B?style=for-the-badge" alt="Threading" />
  <img src="https://img.shields.io/badge/Mutex-4ECDC4?style=for-the-badge" alt="Mutex" />
  <img src="https://img.shields.io/badge/42_Project-000000?style=for-the-badge" alt="42 Project" />
</div>

## 📝 Description

**philosophers** résout le célèbre problème du dîner des philosophes avec des threads et des mutex. Exploration de la programmation concurrente et des problèmes de synchronisation.

## 🛠️ Technologies

- **C** - Programmation système
- **Pthreads** - Threading POSIX
- **Mutex** - Synchronisation et protection des ressources
- **Timing** - Gestion précise du temps

## 🚀 Utilisation

```bash
# Compilation
make

# Lancement
./philo [nb_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nb_meals]

# Exemple
./philo 5 800 200 200 3
```

## 🧠 Le Problème

- **N philosophes** autour d'une table ronde
- **N fourchettes** (une entre chaque philosophe)
- **Actions** - Manger, dormir, penser
- **Règle** - Besoin de 2 fourchettes pour manger
- **Objectif** - Éviter la famine et les deadlocks

## 📋 Fonctionnalités

- **Simulation temps réel** - Chaque philosophe est un thread
- **Protection des ressources** - Mutex pour chaque fourchette
- **Gestion de la mort** - Détection si un philosophe meurt
- **Logs horodatés** - Chaque action est tracée

## 🔄 États des Philosophes

```
[timestamp] [philo_id] is eating
[timestamp] [philo_id] is sleeping  
[timestamp] [philo_id] is thinking
[timestamp] [philo_id] has taken a fork
[timestamp] [philo_id] died
```

## 🏆 Compétences Acquises

- **Threading** - Création et gestion de threads
- **Synchronisation** - Mutex, conditions de course
- **Deadlock prevention** - Stratégies d'évitement
- **Timing précis** - usleep, gettimeofday

## 🎯 Défis Relevés

- **Race conditions** - Protection des données partagées
- **Deadlock** - Prévention des interblocages
- **Performance** - Optimisation des accès concurrents
- **Data races** - Élimination des accès non synchronisés

---

*Projet 42 Paris - Maîtrise de la programmation concurrente et des mutex*
