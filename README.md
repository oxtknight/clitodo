## Clitodo 
A fast, lightweight, and neuro-inclusive CLI task manager written in C.

It is a productivity utility designed to help manage executive dysfunction  by using visual salience, decision-support logic, and mental offloading.

![clitodo-preview](assets/clitodopreview.png) 
### ✨ features
- **Weighted Random Pick:** ADHD-friendly logic that uses a weighted pool (3x weight for `--quick` tasks) to help overcome choice paralysis.
- **Visual Salience:** High-contrast ANSI colors and "dimmed" completion states to improve focus and reduce "wall of text" blindness.
- **Thought Dump:** A quick-capture system (`dump`) to offload mental clutter and "loops" without leaving the flow of work.
- **Gamified Streaks:** Persistent daily streak tracking to reward consistency.
- **File-Based Persistence:** Atomic file updates using temporary buffers to ensure data safety.

### 🧠 What I learnt? 
I deepened my understanding of **File I/O** by implementing a CRUD (Create, Read, Update, Delete) system. I practiced **Memory Management** by using `realloc` for dynamic weighted pools and prioritized **Memory Safety** by replacing `sprintf` with `snprintf`. I also learned how to handle **Linux Time Utilities** (`<time.h>`) to track dates and streaks across sessions.

### ⌨️  Usage:
1. Clone the repository:
```bash
git clone https://github.com/oxtknight/clitodo.git
cd clitodo
```
2. Install globally (Ubuntu/Linux):
```bash
sudo make install
``` 
3. Commands:
 ```bash
clitodo add "Finish reviewing active" --quick
clitodo list
clitodo pick   # Let the app choose your focus
clitodo done 1
clitodo dump "I need to remember to check the stove"
```

### ✅ Future improvements
- priority system 
- timer mode
- reward system 
- idk probably something in this theme :>

