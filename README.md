TopoAna: A generic tool for the topology analysis of inclusive Monte-Carlo samples in high energy physics experiments

Inclusive Monte-Carlo samples are indispensable for signal selection and background suppression in many high energy physics experiments. A clear knowledge of the topology of the samples, including the categories of physics processes and the number of processes in each category, is a great help to investigating signals and backgrounds. To help analysts get the topology information from the raw data of the samples, we develop a topology analysis program, TopoAna, with C++, ROOT, and LaTeX. The program implements the functionalities of component analysis and signal identification by recognizing, categorizing, counting, and tagging events. Independent of specific software frameworks, the program is applicable to many experiments. At present, it has come into use in three $e^+e^-$ colliding experiments: the BESIII, Belle, and Belle~II experiments. The use of the program in other experiments is also prospective.

1. How to install the program

   (1) Configure the program with the following command: ./Configure

       Notably, you are recommended to manually set up the environment variable ''PATH'' according to the suggestion output by the command.

       Executing the command and setting the ''PATH'' once is sufficient, unless the package is moved.

   (2) Compile the program with the following command: make

       Executing the command once is sufficient unless the C++ header, source, or script files are updated or revised, or the package is moved.

2. How to use the program

   (1)

   (2) An essential description of the program is in the document: share/paper_draft_v1.1.pdf

   (3) A detailed description of the program is in the document: share/user_guide_v3.7.pdf

