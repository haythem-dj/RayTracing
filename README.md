# RayTracing
A Ray Tracer that is written in c++

## How to build
- To build you need the HEngine framework and GLM

> Run this command to build the engine

```bash
g++ -DUNICODE -c HEngine/src/*.cpp -I HEngine/include -lgdi32 && move *.o bin && ar rvs lib/libHEngine.a bin/*.o
```

> Run this command to build the project

```bash
g++ -DUNICODE src/*.cpp -I HEngine/include -I glm/glm -I include -L lib -lHEngine -lgdi32 -o main
```