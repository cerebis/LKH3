LKH is an implementation of the Lin-Kernighan traveling salesman heuristic.

The code is distributed for research use. The author reserves all rights to 
the code.


INSTRUCTIONS FOR INSTALLATION: (Version 3.0.2 - April 2018)
-----------------------------

The software is available in gzipped tar format:

	LKH-3.0.2.tgz	(approximately 2 MB)

Download the software and execute the following UNIX commands:

  	tar xvfz LKH-3.0.2.tgz
   	cd LKH-3.0.2
	make

An executable file called LKH will now be available in the directory LKH-3.0.2.

To test the installation run the program by typing ./LKH pr2392.par. 
Then press return. The program should now solve a TSP instance with 2392 nodes.

For testing the installation on an mTSP problem, type ./LKH whizzkids96.par.
Then press return.

A two-level tree is used as the default tour representation. 
A three-level tree representation may be used instead by compiling the
source code with the compiler option 

	-DTHREE_LEVEL_TREE

Just edit the first line in SRC/Makefile and execute the commands

	make clean
	make

CHANGES IN VERSION 3.0.2:
-------------------------

Tours may now be recombined by GPX2 (Generalized Partition Crossover 2) 
instead of IPT (Iterative Partial Transcription). 

GPX2 is used by giving the following specification in the parameter file:

	RECOMBINATION = GPX2

The possible settings are:

	RECOMBINATION = { IPT | GPX2 } 

IPT is default.

	
CHANGES IN VERSION 3.0.1:
-------------------------

    New problem type: TSPDL (traveling salesman with draft limits)

NEW IN VERSION 3.0:
-------------------
	
New parameter keywords:

	BWTSP = <integer> <integer> [ <integer> ]
	DEPOT = <integer>
	MAKESPAN = { YES | NO }	MTSP_MIN_SIZE = <integer>
	MTSP_MAX_SIZE = <integer>
	MTSP_OBJECTIVE = [ MINMAX | MINMAX_SIZE | MINSUM ]
	MTSP_RESULT_FILE = <string>
	SINTEF_RESULT_FILE = <string>
	SALESMEN = <integer>
	SCALE = <integer>
	VEHICLES : <integer>

	New initial tour algorithms:
	CVRPR
	MTSP
	SOP 

New TSPLIB format keywords:

The specification part: 

	CAPACITY : <integer>
	DEMAND_DIMENSION : <integer>
	DISTANCE : <real>
	GRID_SIZE : <real>
	RISK_THRESHOLD : <integer>
	SALESMEN : <integer>
	SCALE : <integer> 
	SERVICE_TIME_SECTION 
	VEHICLES : <integer>

	New edge weight types:	
	EXACT_2D
	EXACT_3D 
	FLOOR_2D
	FLOOR_3D
	TOR_2D
	TOR_3D 

The data part: 

	BACKHAUL_SECTION
	DEMAND_SECTION
	DEPOT_SECTION
	PICKUP_AND_DELIVERY_SECTION
	TIME_WINDOW_SECTION
