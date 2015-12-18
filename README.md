#Infection Detection

**Target: IDENTIFY the infection category.**

**Method:**

	1. GENERATE CARDS of GENEs, fixed LENGTH as 8.

	2. FIND all PATTERNS in GENOME code.(From human, bacteria, virus, etc.)

	3. STORE statistical information of cards on disk. CREATE method to load them into memory fast.

	4. FIND all PATTERNS in GENOME code.(From test samples given correct labels.)

	5. BUILD NEURAL NETWORK.

	6. TRAIN the Neural Network.

	7. PREDICT LABELS of test samples and RATE the prediction correctness.

	8. APPLY the model to SAMPLE D & E.

	9. WRITE a report of this project. 

**GENETIC ENCODING METHOD:**

	1. Encoding: A:00, C:01, G:10, T:11

	2. Example: AATTGGCC=>0000111110100101(2 byte)

**NOTICE:**

	1. PLEASE BUILD HUMAN LIB FIRST!
	
	2. THEN BUILD INFLUENZA, VIRUS, ETC.

	3. LIKELY, BUILD TEST CASE A FIRST, THEN B AND C.

	4. NOTATION FILE IS ALWAYS LINKED WITH INDEX FILE.

**TRAIN:**
	
	1. (1<<(8x2)) = 65536
	2. 65536/8 = 8192 => Feature Extraction
	3. 8192x9847 index
	4. stored in 9847 x (8192x4) [int] memory
	5. write them into 8192 x (9847x4) [float] disk

