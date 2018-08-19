all:
	g++ -Wall -g -c common/*.cpp -lglut32cu -lglu32 -lopengl32
	g++ -Wall -g -c objects/*.cpp -lglut32cu -lglu32 -lopengl32
	g++ -Wall -g -c objects/actors/*.cpp -lglut32cu -lglu32 -lopengl32
	g++ -Wall -g -c interface/*.cpp -lglut32cu -lglu32 -lopengl32
	g++ -Wall -g -c interface/text/*.cpp -lglut32cu -lglu32 -lopengl32
	g++ -Wall -g -c simulation/*.cpp -lglut32cu -lglu32 -lopengl32
	g++ -Wall -g *.cpp *.o -o projexec.exe -lglut32cu -lglu32 -lopengl32
	del *.o

clean:
	del *.o