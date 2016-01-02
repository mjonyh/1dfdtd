import numpy as np   
from matplotlib import pyplot as plt   
from matplotlib import animation

data = np.loadtxt("frame.log")

fig = plt.figure()
#plt.xlim(0, 100)
plt.ylim(-1, 1)
images = []
x = []

for i in range(len(data[1,:])):
	x.append(i*0.3)

for i in range(len(data)):
	#print i
	#x = data[i]
	y = data[i, :]
	#print y
	#print len(y)
	plt.title("Time in ns")
	plt.ylabel("Normalized Amplitude (in a.u.)")
	plt.xlabel("Position (in m)")
	im = plt.plot(x, y, "b", lw=3)
	#plt.show()

	images.append(im)



ani = animation.ArtistAnimation(fig, images, interval=10, 
							blit=True, repeat_delay=2000)
#ani.save('dynamic_images.mp4')

plt.show()
