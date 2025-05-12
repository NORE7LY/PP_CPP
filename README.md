# Sports Activity Tracking System (C++)

A comprehensive console-based application for tracking various sports activities with detailed analytics, goal setting, and progress visualization.

## Features

- **Multiple Activity Types**: Track running, walking, swimming, cardio, and strength training.
- **Data Persistence**: Automatically saves and loads activities to/from CSV files.
- **Advanced Search & Filter**: Find activities by keyword, type, date range, or duration.
- **Detailed Statistics**: View averages and totals for each activity type.
- **Data Visualization**: ASCII-based charts to visualize progress over time.
- **Goal Setting & Tracking**: Set personal fitness goals and monitor progress.
- **Activity Summary Reports**: Get detailed breakdowns by activity type, date, and more.
- **Input Validation**: Robust validation for dates and numeric inputs.
- **Color-Coded Interface**: Easy-to-navigate terminal UI with color highlights.

## Setup & Installation

### Prerequisites
- C++ compiler with C++11 support
- Standard I/O libraries

### Compilation
Compile the application with C++11 support:

```bash
g++ -std=c++11 main.cpp tracker.cpp -o activity_tracker
```

### Running the Application
After compilation, run the executable:

```bash
./activity_tracker
```

## Usage Guide

### Main Menu Navigation
The application provides an intuitive menu system with the following options:

1. **Add Activity** - Record a new workout session
2. **View Activities** - Display all recorded activities
3. **Search Activities** - Find specific activities by keyword or date
4. **Filter Activities** - Filter by type, date range, or duration
5. **View Statistics** - Show performance analytics
6. **Show Progress Chart** - Visualize your progress with ASCII charts
7. **Set New Goal** - Create personal fitness targets
8. **View Goals & Achievements** - Track progress toward goals
9. **Backup Data** - Save your data for safekeeping
0. **Exit** - Close the application

### Recording Activities
When adding a new activity:
1. Select the activity type (running, walking, swimming, etc.)
2. Enter the date (YYYY-MM-DD format)
3. Input the duration in minutes
4. For distance-based activities, enter distance in kilometers
5. For strength training, enter the number of repetitions

### Setting Goals
The goal system allows you to:
1. Define specific targets for any activity type
2. Set deadlines for completion
3. Track progress automatically
4. Receive notifications when goals are achieved

## Data Storage

Activities and goals are stored in CSV files:
- Activities: `[filename].csv`
- Goals: `[filename]_goals.csv`

These files are automatically loaded when the program starts and saved when the program exits.

## Technical Details

### Activity Types
- Running
- Walking
- Swimming 
- Cardio
- Strength

### Data Structure
Each activity stores:
- Activity type
- Date (YYYY-MM-DD)
- Duration (minutes)
- Distance (km) for applicable activities
- Repetitions for strength training

### Implementation Details
- Written in C++ with C++11 features
- Uses STL containers (vector, map, set)
- RAII principles for resource management
- Exception handling for robust operation
- Comprehensive input validation

## Contributing

Feel free to contribute to this project by:
1. Forking the repository
2. Creating a feature branch
3. Submitting a pull request

## License

MIT License

Copyright (c) 2023

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 