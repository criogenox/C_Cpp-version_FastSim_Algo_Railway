[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<div align="center">
  <a align="center">
    <img src="https://github.com/criogenox/D-Technical-Railway-Data-Viewer-from-SQLitedb/assets/53323058/55f51d41-fda0-4161-881c-8144ad315c00.png" alt="Logo" width="500">
  </a>
  <h3 align="center">Railway applications &#x300A; C &#x300B;</h3>
  <p align="center">
    Kalker's FastSim algorithm C++ library
  </p>
</div>

## About the project

<div align="justify">
  <p>
  
> `C++` version of Kalker's FastSim algorithm, designed for simulating rolling contact dynamics based on the simplified theory. Despite the time elapsed since its development, it efficiently calculates the forces acting on contact patch providing valuable insights for engineering simulations.

`Why this repo?:`
- In order to provide a C++ version of a helpful contact algorithm, that regardless of being classic simulation code, no one shares it.
   
   </p>
       <p align="right">
    :muscle: don't let anyone get you down :muscle:
  </p> 
   <div>

## Built With

<div style="display: flex; flex-direction: column; align=center">
    <img class="img"src="https://github.com/criogenox/B_ECC-Cpp-version_plot-capabilities_noGUI/assets/53323058/1fdf2d22-fb04-45aa-9db0-8bd973942914.png" alt="Logo" width="90" height="80"/>
    <img class="img"src="https://github.com/criogenox/B_ECC-Cpp-version_plot-capabilities_noGUI/assets/53323058/6870b0b2-403c-49da-b745-5714b08f4a73.png" alt="Logo" width="90" height="80"/>
    <img class="img"src="https://github.com/criogenox/B_ECC-Cpp-version_plot-capabilities_noGUI/assets/53323058/7f7c66db-97e3-49a1-92d9-df41500b54ae.png" alt="Logo" width="90" height="90"/>
</div>

### Additional info

<div align="justify">
  <p>
    
> CMake configuration to building the application: several targets for a specific role, enabling better management of source files, libraries, and testing processes.

`TARGET_SRC`
- It compiles the entire source files of the project into an executable.

`TARGET_LIB`
- It creates a static library from the specified source files.
- It is linked to the main program as entry point to test its funcionality

`TARGET_TEST`
- It compiles the test files enabling the run of unit tests according to the author's checking data.
- It executes linked against the GoogleTest libraries (gtest_main, gmock_main) and the TARGET_LIB.

> Google Test (gtest) C++ testing framework to carry out and handled correctly well-structured checks ensuring the code results reliability.

`Parameterized Tests:`
- It runs multiple test cases with input checking data provided by the original author. 
- It uses ASSERT_NEAR macro to compare floating-point results with a specified tolerance.
  
`Setup and Teardown:`
- A method is implemented to perform any necessary initialization before running the first test, and to improve the measure of time execution.

`Benchmarking:`
- It includes timing functionality to measure the computation time for each test case.

`Error Handling:`
- The parameterized implementation ensures achieving the complete set of tests even in the event of an invalid test result.
   </p>
   <div>

##  General view sample

<div align="justify"> 
  <!-- <img align="right" src="https://user-images.githubusercontent.com/53323058/230650942-4c2e0ad4-2d52-46fe-aa67-8860c642e5f6.png" width="500"> -->
<img align="right" src="https://github.com/criogenox/D-Technical-Railway-Data-Viewer-from-SQLitedb/assets/53323058/8f6aca0c-716b-4f33-9a34-3e455d366d25.png">
   </p>
       <p align="center">
Full functionalities in use:  clickable table index, independent views with their corresponding dock info.
  </p> 
</div>

<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE.txt][license-url] for more information.

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://user-images.githubusercontent.com/53323058/230575198-fa1acbf4-8f82-4d8e-b245-3979276bc240.png
[linkedin-url]: https://www.linkedin.com/in/criogenox/
[qtdarktheme-url]: https://github.com/keshav-sahu7/qt-dark-theme
[license-url]: https://github.com/criogenox/D-Technical-Railway-Data-Viewer-from-SQLitedb/tree/main?tab=MIT-1-ov-file
