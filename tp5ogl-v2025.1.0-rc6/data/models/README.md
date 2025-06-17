# 3D Model Collection

Here you can find some 3D models in OBJ format that you can use to test the visualizer and the different algorithms.

There are very simple and basic models like the `square` and the `cube` that are useful for debugging (very few vertices and faces).

The `cow` and the `teapot` come in two version, manifold and non manifold. Non manifold means that a model tha can have duplicated vertices or edges: in the case of the cow, for example, the model was built by putting together two symmetric halves of the model, without merging the common edges and vertices.
This is not a problem for the visualizer, but it is a problem for the subdivision algorithms like Loop, that will create a lot of artifacts.
You can try both versions to see the difference.

## Stanford Models

The models in the `standard` folder are models from the [Stanford 3D Scanning Repository](http://graphics.stanford.edu/data/3Dscanrep/). 
These models are used in the literature to test algorithms, so they are a good benchmark for the visualizer and the algorithms.
They are usually large models, you can use them to test the performance of the visualizer to see the difference in performance (the frame per second, FPS) when comparing the vertex array rendering and the face rendering.
Avoid using the larger models to test the Loop's subdivision algorithm, as it is very slow and will take a lot of time to complete. 