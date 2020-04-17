Merge "rve_mesh3_0.stl";
Merge "rve_mesh3_1.stl";


Surface Loop(1) = {1};// matrix
Surface Loop(2) = {2};// particles
//+
Volume(1) = {1};
//+
Volume(2) = {2};
//+
Physical Volume("matrix") = {1};
Physical Volume("particle") = {2};
//+


Mesh 3;
Coherence;
Mesh save;
