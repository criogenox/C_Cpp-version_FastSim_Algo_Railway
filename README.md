[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<div align="center">
  <a align="center">
    <img src="https://github.com/criogenox/C_Cpp-version_FastSim_Algo_Railway/assets/53323058/6ce23006-ff6e-46dd-b5de-56f1fbb6750b.png" alt="Logo" width="500">
  </a>
  <h3 align="center">Railway applications &#x300A; C &#x300B;</h3>
  <p align="center">
    Kalker's FastSim algorithm C++ library
  </p>
</div>

## About the project

<div align="justify">
  <p>
  
> `C++` version of Kalker's FastSim algorithm, designed for simulating rolling contact dynamics based on the simplified theory. Despite the time elapsed since its development, it efficiently calculates the forces acting on the contact patch, providing valuable insights for engineering simulations.

`Why this repo?:`
- In order to provide a C++ version of a helpful contact algorithm, that regardless of being a classic simulation code, no one shares it.
   
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

### Additional info

<div align="justify">
  <p>

> Google Test (gtest) C++ testing framework to carry out and handled correctly well-structured checks ensuring the code results reliability.

`Parameterized Tests:`
- It runs multiple test cases with a vector of doubles input as checking data, provided by the work's author. 
- It uses ASSERT_NEAR macro to compare floating-point results with a specified tolerance.
  
`Setup and Teardown:`
- A method was implemented to perform any necessary initialization before running the first test, and to improve the measure of time of execution.

`Benchmarking:`
- It includes timing functionality to measure the computation time for each test case.

`Error Handling:`
- The parameterized implementation ensures the execution of the complete tests set, even in the event of an invalid test result.
  
> CMake configuration: added several targets for a specific role, enabling better management of source files, libraries, and testing processes.

`TARGET_SRC`
- It compiles the entire source code of the project into an executable.

`TARGET_LIB`
- It creates a static library from the specified source files.
- Its functionality testing is done by linking to the main program as entry point.
  
`TARGET_TEST`
- It compiles the test files, enabling the run of unit tests according to the author's checking data.
- It executes linked against the GoogleTest libraries (gtest_main, gmock_main) and the TARGET_LIB.
   </p>
   <div>

<p align="right">(<a href="#top">back to top</a>)</p>

##  Output view sample

<div align="justify"> 
  <!-- <img align="right" src="https://user-images.githubusercontent.com/53323058/230650942-4c2e0ad4-2d52-46fe-aa67-8860c642e5f6.png" width="500"> -->
<img align="center" src="https://github.com/criogenox/C_Cpp-version_FastSim_Algo_Railway/assets/53323058/41b73459-f5b6-4efe-b6f5-b74f9c42cdc9.png">
   </p>
       <p align="center">
Test's full output: execution time, test tagging, and detailed results (especially when it fails)
  </p> 
</div>

<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE.txt][license-url] for more information.

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://user-images.githubusercontent.com/53323058/230575198-fa1acbf4-8f82-4d8e-b245-3979276bc240.png
[linkedin-url]: https://www.linkedin.com/in/criogenox/
[license-url]: https://github.com/criogenox/C_Cpp-version_FastSim_Algo_Railway/tree/master?tab=MIT-1-ov-file
