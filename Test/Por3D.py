import numpy as np

w1=35.0;w2=15.0 # thickness=w1+w2
h=4.0

bulkmeshsize=1.2
surfacemeshsize=0.8

####################################
### parameters for the balls
####################################
tol=1.0e-1
Radius=0.8
R0min=0.8
nBalls=50

np.random.rand()

def GenerateBall(R0):
    Xmin=w1+R0min+tol;Xmax=w1+w2+tol
    Ymin=tol+R0;Ymax=h-tol-R0
    Zmin=tol+R0;Zmax=h-tol*2
    x=Xmin+(Xmax-Xmin)*np.random.rand()
    y=Ymin+(Ymax-Ymin)*np.random.rand()
    z=Zmin+(Zmax-Zmin)*np.random.rand()
    radius=R0min+R0*np.random.rand()
    return x,y,z,radius

filename='dns.geo'

inp=open(filename,'w+')
inp.write('algebraic3d\n\n')

#first we create a cubic for the cell
str='solid cube = orthobrick (0, 0, 0; %g, %g, %g) -maxh=%g;\n'%(w1+w2,h,h,bulkmeshsize)
inp.write(str)

str='solid balls= '
for i in range(nBalls):
    x,y,z,r=GenerateBall(Radius)
    if i==0:
        str+='sphere(%g,%g,%g;%g)\n'%(x,y,z,r)
    else:
        str+='\t or sphere(%g,%g,%g;%g)\n'%(x,y,z,r)
str+='\t -maxh=%g;\n\n'%(surfacemeshsize)
inp.write(str)


str='solid domain1=cube and not balls;\n\n'
str+='solid domain2=balls and cube;\n\n'

str+='tlo domain1 -col=[0,0,1] -transparent;\n'
str+='tlo domain2 -col=[1,0,1];\n'
inp.write(str)

inp.close()

print('write mesh to %s'%(filename))