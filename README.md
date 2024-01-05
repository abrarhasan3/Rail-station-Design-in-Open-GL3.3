# Rail-station-Design-in-Open-GL3.3

This project showcases a visually engaging scene of a railway station created using Modern OpenGL (3.3). Leveraging the power of shaders, vertex buffers, and textures, the implementation brings to life a dynamic and immersive representation of a bustling railway environment.

This project includes implimentation on:
- Vertex Shader and Fragment Shader
- Lighting (Point Light, Directional Light, Spot Light)
- Texture
- Bézier curve

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
- [Controls](#controls)
- [Demo](#demo)
- [Tutorial](#tutorial)
- [Contributing](#contributing)
- [License](#license)
- [Authors](#authors)

## Features

- **Modern OpenGL (3.3):** Utilizes the latest OpenGL features for efficient rendering and realistic graphics.
- **Shader Programs:** Implements vertex and fragment shaders to achieve lifelike lighting and shading effects.
- **Texture Mapping:** Applies textures to various elements within the scene for enhanced visual realism.
- **Bézier curve:** Impliments Bézier curve to create realistic curvy objects like pillers, wheel, face of train. 
- **Dynamic Elements:** Introduces dynamic elements such as moving trains, rotating fan and changing lighting conditions.
- **User Interaction:** Allows users to navigate and explore the railway station scene interactively.
- **Cross-Platform:** Designed to work seamlessly across different platforms.

## Requirements

To run this project, ensure that you have the following dependencies installed:

- OpenGL 3.3 or later
- GLFW (OpenGL framework)
- GLAD (OpenGL loader)
- GLM (OpenGL Mathematics)
- Visual Studio 2022

## Usage
1. Install the visual studio
2. Clone the repository:

   ```bash
   git clone https://github.com/your-username/railway-station-scene.git
3. Open the project.sln file
4. Fix the OpenGL path (For tutorial See the [Tutorial](#tutorial) Section) 
5. Run the project

## Controls



| KEY  | Operation | Visual Effect |  | | KEY  | Operation | Visual Effect | | | KEY  | Operation | Visual Effect | 
| :-------------: | :-------------: | :-------------: |:-------------: |:-------------: | :-------------: | :-------------: | :-------------: |:-------------: |:-------------: | :-------------: | :-------------: | :-------------: |
|  <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/assets/85815740/c2878424-81d2-4567-ac7f-5e3c40fdf42c" height = "50" width = "50"> | Move Front  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/assets/85815740/dd497508-6fd3-4f06-a431-5c28d33e620a" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/S.png" height = "50" width = "50"> | Move Back  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Back.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/P.png" height = "50" width = "50"> | Door Open  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Door%20Open.png" height = "50" width = "50">|
|  <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/A.png" height = "50" width = "50"> | Move LEFT  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Left.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/D.png" height = "50" width = "50"> | Move Right  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Right.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/O.png" height = "50" width = "50"> | Door Close  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Door%20Close.png" height = "50" width = "50">|<br>
|  <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/E.png" height = "50" width = "50"> | Move Up  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/UP.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/F.png" height = "50" width = "50"> | Move Down  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Down.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/L.png" height = "50" width = "50"> | Move Train  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Move%20Train.png" height = "50" width = "50">|
|  <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/k.png" height = "50" width = "50"> | Roll Left  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Roll%20Left.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/J.png" height = "50" width = "50"> | Roll Right  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Pitch.png" height = "50" width = "50"> |  | | <img src ="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/H.png" height = "50" width = "50"> | Move Train  | <img src="https://github.com/abrarhasan3/Rail-station-Design-in-Open-GL3.3/blob/main/Images/Turn%20on%20fan.png" height = "50" width = "50">|




 


   




## Demo



## Tutorial 
Setup Environment : <a href= "https://youtu.be/WoTRZ0t1tT4?si=uxiBXIGt65EZqlh5">Click Here for Tutorial </a>

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

Fork the project.
- Create your feature branch: git checkout -b feature/YourFeature.
- Commit your changes: git commit -m 'Add some feature'.
- Push to the branch: git push origin feature/YourFeature.
- Open a pull request.

## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/). Feel free to use, modify, and distribute the code for your purposes.

## Authors

- [Abrar Hasan](https://www.github.com/abrarhasan3)
