<h1> Delynoi: an object-oriented C++ library for the generation of polygonal meshes</h1>
This repository contains the code for an open source C++ library for the generation of polygonal meshes on arbitrary domains,
based on the constrained Voronoi diagram.

Features:
<ul>
<li> The meshes are generated on arbitrary domains, created from user points. Domains have no restrictions on convexity. </li>
<li> It allows the inclusion of completely contained or intersecting holes, which are processed if required. </li>
<li> The meshes are generated from seed points, which can be either read directly from a text file, included one by one, 
or created from a number of generation rules included in the library. New generation rules can be included easily. </li>
<li> Meshes can be stored in OFF-style text files, or used directly on another program. </li>
<li> To generate the meshes, the library first obtains the conforming Delaunay triangulation using Triangle; the triangulation
is considered a mesh that is left available for use in case it is desired. Then, it computes the constrained Voronoi diagram.</li>
</ul>

<h2>Author</h2>
<a href="https://github.com/capalvarez">Catalina Alvarez</a> -  Master's Student at Universidad de Chile.

<h2>Usage instructions</h2>
Delynoi is currently for Unix systems only.
<ol>
<li> Download the source code and unpack it. </li>
<li> In the root directory of Veamy, create a <b>build/</b> folder.</li>
<li> Go to test/ folder located in the root directory of Delynoi and: (a) add the main C++ file 
(say, <b>mytest.cpp</b>) containing your test example problem, (b)  modify the <b>CMakeLists.txt</b> 
by changing the file name <b>example.cpp</b> in <pre><code>set(SOURCE_FILES example.cpp)</pre></code></li> by the name 
of your main C++ file (in this case, <b>mytest.cpp</b>)
<li> Inside the <b>build</b> folder and in the command line type:
<pre><code>cmake .. </code></pre> to create the makefiles. And to compile the program type:
<pre><code>make </code></pre></li>
<li> To run your example, go to the <b>build/test/</b> folder and in the command line type:
<pre><code>./Test</pre></code> 
</ol>

<h2>Usage example</h2>
To generate a polygonal mesh in any desired domain, one needs to:
<ol>
<li> List, in counter clockwise order, the points that define the domain and 
create the domain as a Region instance: <br>
<pre><code>std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
Region square(square_points);   </pre></code></li>
<li> Include the required seed points on the domain, for which there are three alternatives:
<ol>
<li> Create the desired points as a list of Point instances, and call: <br>
<pre><code>std::vector<Point> seeds = {Point(5,5)};
square.addSeedPoints(seeds);
</code></pre></li>
<li> With the points coordinates listed on a text file, say <b>seeds.txt</b> (an example is found in the
test folder), call: <br>
<pre><code>square.addSeedsFromFile("seeds.txt");</code></pre></li> 
<li> Decide on two generation rules (one for each axis) from the predifined list of functions (or create a new one inheriting 
following the instructions found on the manual), and create a PointGenerator instance. If required, include a noise function 
from the noise list provided. Then, call, including the PointGenerator and the number of 
points on each axis: <br>
<pre><code>PointGenerator rules(functions::random_double(0,10), functions::random_double(0,10));
int nX = 5, nY = 5;
square.generateSeedPoints(rules, nX, nY); </code></pre></li>
</ol>
<li> Create a TriangleVoronoiGenerator instances with the points inside the domain, and the domain
itself:<br>
<pre><code>std::vector<Point> seeds = square.getSeedPoints();
TriangleVoronoiGenerator generator (seeds, square);</code></pre></li>
<li> To obtain the Voronoi diagram, call: <br>
<pre><code>Mesh&ltPolygon&gt voronoi = generator.getMesh();</code></pre></li>
<li> To use the Delaunay triangulation instead of the Voronoi diagram, a different class is used, TriangleDelaunayGenerator,
which can return the constrained Delaunay triangulation or the conforming Delaunay triangulation:
<pre><code>TriangleDelaunayGenerator generator (seeds, square);
Mesh&ltTriangle&gt constrained_delaunay = generator.getConstrainedDelaunayTriangulation();
Mesh&ltTriangle&gt conforming_delaunay  = generator.getConformingDelaunayTriangulation();</code></pre>
It is also possible to define a number of constrained segments inside the domain, that will not be flipped
when the Delaunay triangulation is computed:
<pre><code>Mesh&ltTriangle&gt constrained_delaunay = generator.getConstrainedDelaunayTriangulation(restrictedSegments);
</code></pre>
<li> To write any mesh (either of polygons or triangles) on a text file: <br>
<pre><code>mesh.printInFile("mesh.txt");</code></pre></li>
</ol>

<h2>Acknowledgements</h2>
Delynoi depends on two external open source libraries, whose code is included in the repository.
<ul>
<li> <a href="https://www.cs.cmu.edu/~quake/triangle.html"> Triangle - A Two-Dimensional Quality Mesh Generator and 
Delaunay Triangulator. </a></li>
<li><a href="http://www.angusj.com/delphi/clipper.php"> Clipper - an open source freeware library for clipping and offsetting lines and polygons. </a></li>
</ul>

<h2>License</h2>
This project is licensed under the GPL License. This program is free software; 
it can be redistributed or modified under the terms of the GNU General Public License as published by
the Free Software Foundation.
