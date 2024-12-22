# PatiTin_2: Task Management and Time Planning Application  

**PatiTin_2** is a task management application designed to help users plan and organize their time effectively. Inspired by a traditional To-Do List, this program offers features that improve efficiency and collaboration, ensuring a streamlined approach to personal and team task management.  

## Key Features  
- **Task Scheduling and Prioritization**  
  - Add tasks with a name, date, time, and priority level.  
  - View tasks scheduled for a specific day.  
  - Search for tasks based on the date.  
  - Organize tasks by priority to focus on what matters most.  

- **Effective Time Management**  
  - Plan time effectively by setting priorities for tasks.  
  - Allocate time for tasks based on their importance.  

- **Collaboration Support**  
  - Share tasks with teammates or close collaborators.  
  - Manage group projects by assigning shared tasks, improving team efficiency.  

## Data Structures Used  
- **Priority Queue**: Stores tasks ordered by the nearest due time.  
- **Stack**: Keeps track of completed tasks in chronological order.  
- **Linked List**: Facilitates interaction with the priority queue.  
- **Tree (Forest)**: Organizes data by year, month, day, and associated tasks.  
- **Array**: Stores yearly data, working in conjunction with the tree and stack.  

## Core Algorithm  
1. Create a forest structure with the root representing the year.  
2. When a new task is added:  
   - Specify the date, time, task name, and priority.  
   - Allocate memory dynamically if no previous task exists for the specified month or day.  
3. Utilize the following structures:  
   - **Priority Queue** to sort tasks by starting time, with earlier tasks appearing first.  
   - **Stack** to store completed tasks.  
4. Tasks with identical start times are prioritized based on the order of creation.  

PatiTin_2 is designed to optimize task planning, improve time management, and enhance collaboration in both personal and team environments.
