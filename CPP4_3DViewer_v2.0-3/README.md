# 3DViewer v2.0

Implementation of 3DViewer v2.0


## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
   2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
   3.1. [Part 1](#part-1-3dviewer-v20) \
   3.2. [Part 2](#part-2-bonus-settings) \
   3.3. [Part 3](#part-3-bonus-record)


## Chapter I

## Introduction

In this project you’ll need to implement an application for viewing 3D wireframe models in C++ in the object-oriented programming paradigm, implementing the same functions as the previously developed application in 3DViewer v1.0 project.


## Chapter II

## Information

### Design patterns

Any human activity, such as cooking or nuclear physics experiments, has a set of established practices that deal with basic elementary tasks. They do not require an individual approach and are usually solved by well-established approaches developed over time, based on the experience of previous cooks or nuclear physicists. For example, baking a cake, even an unusual one, is likely to require dough whose cooking technology is known in advance and does not usually require any creativity. It's the same with programming: when designing, you often have elementary tasks that a large number of programmers have faced before you, and their experience has developed into established design patterns.

**Design pattern** describes a frequently recurring application design problem and a universal way of solving it.
In other words, to a programmer, a design pattern is nothing more than a building block, an elementary unit that is implemented when a typical subtask occurs within a project.

Design patterns are usually divided into three groups: creative, structural and behavioural. See Resources for more information about design patterns. \
You have already encountered the use of established practices (patterns) in application design in the SmartCalc v2.0 project (MVC pattern). As a reminder, MVC in one form or another is one of the most common solutions in terms of code structuring during UI application development.
The user interface and the business logic with its controller are usually separated into two different global domains: the interface domain and the business logic domain.

The interface domain is only responsible for displaying the interface and passing commands to the business logic domain. Data loaded from a file should not be stored in the interface domain.

The business logic domain is responsible for the main functionality of the system. This is where the loaded data is stored and all operations on it are performed. This is also where the rendering takes place.

You can see an example of a suggested class diagram for a business logic domain in materials.


## Chapter III

## Part 1. 3DViewer v2.0

Develop a program to visualise the 3D wireframe models.

- The program must be developed in C++ language of C++17 standard;
- The program code must be located in the src folder;
- When writing code it is necessary to follow the Google style;
- The program must be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. Installation directory could be arbitrary, except the building one;
- The program should be developed according to the principles of object-oriented programming; the structured programming approach is not allowed;
- Prepare full coverage of modules related to model loading and affine transformations with unit-tests;
- There should be only one model on the screen at a time;
- The program must provide the ability to:
    - Load a wireframe model from an obj file (vertices and surfaces list support only);
    - Translate the model by a given distance in relation to the X, Y, Z axes;
    - Rotate the model by a given angle in relation to its X, Y, Z axes;
    - Scale the model by a given value;
- GUI implementation, based on any GUI library with API for C++:
  * For Linux: GTK+, CEF, Qt, JUCE;
  * For Mac: GTK+, CEF, Qt, JUCE, SFML, Nanogui, Nngui;
- The graphical user interface must contain:
    - A button to select the model file and a field to output its name;
    - A visualisation area for the wireframe model;
    - Button/buttons and input fields for translating the model;
    - Button/buttons and input fields for rotating the model;
    - Button/buttons and input fields for scaling the model;
    - Information about the uploaded model - file name, number of vertices and edges;
- The program must correctly processes and allows user to view models with details up to 100, 1000, 10,000, 100,000, 1,000,000  vertices without freezing (a freeze is an interface inactivity of more than 0.5 seconds);
- The program must be implemented using the MVC pattern, and also:
    - there should be no business code in the view code;
    - there should be no interface code in the controller and the model;
    - controllers must be thin;
- There should be at least three different design patterns (e.g. facade, strategy and command);


## Part 2. Bonus. Settings

- The program must allow customizing the type of projection (parallel and central);
- The program must allow setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices;
- The program must allow choosing the background color;
- Settings must be saved between program restarts.

## Part 3. Bonus. Record

- The program must allow saving the captured (rendered) images as bmp and jpeg files;
- The program must allow recording small screencasts - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s) by a special button.

