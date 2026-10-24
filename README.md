
# Digital Twin-Based Temperature Monitoring, Prediction and Control of a Thermal Process

## Digital Twin Challenge 2026

A Digital Twin-based thermal process monitoring and prediction system integrating real-time temperature acquisition, mathematical modelling, machine learning-based forecasting, early warning, and virtual process visualization.

---

## 1. Team Details

| Team Member | Roll Number |
|---|---|
| Boopathi N | 23U207 |
| Dhanushveer Singh P | 23U208 |
| Dharneesh E | 23U210 |
| Naveen N | 23U228 |

## 2. College / Institution Information

- **Institution:** PSG College of Technology
- **Department:** Instrumentation and Control Engineering
- **Location:** Coimbatore, Tamil Nadu, India
- **University:** Anna University

## 3. Project Title

Digital Twin-Based Temperature Monitoring, Prediction and Control of a Thermal Process

## 4. Problem Statement

Conventional thermal process monitoring systems primarily provide real-time temperature measurements without necessarily incorporating predictive capabilities or a synchronized virtual representation.

This limits the ability to anticipate temperature threshold violations and understand the future behaviour of a thermal process.

This project addresses these challenges through a Digital Twin-based framework that integrates physical temperature acquisition, mathematical modelling, machine learning-based prediction, early warning, and virtual process visualization.

An electric kettle is used as a thermal prototype to demonstrate the proposed methodology.

## 5. Project Overview

The proposed system integrates a physical thermal process with a virtual representation.

A DS18B20 digital temperature sensor measures the water temperature inside an electric kettle. An ESP32 acquires and processes the temperature data.

The system incorporates:

- Real-time temperature monitoring
- Thermal energy-balance modelling
- Linear Regression-based temperature prediction
- One-step-ahead temperature forecasting
- Ten-step recursive temperature prediction
- Adaptive historical prediction windows
- Prediction error evaluation using MAE
- Threshold-based early warning
- MQTT-based temperature communication
- SolidWorks-based 3D kettle modelling
- Unity-based virtual process representation

## 6. Healthcare Use Case

The current project focuses on industrial thermal process monitoring and is not a healthcare application.

The system demonstrates temperature acquisition, prediction, and early-warning concepts using an electric kettle as a thermal prototype.

A healthcare-specific use case has not been implemented.

The applicability of this project to the competition's healthcare-use-case requirement requires clarification.

## 7. Technical Stack

### Hardware

- ESP32 DevKit
- DS18B20 digital temperature sensor
- Electric kettle thermal prototype
- Sensor interface: 1-Wire
- Sensor data pin: GPIO 4

### Software

- Arduino IDE
- Embedded C/C++
- Python
- MQTT
- Mosquitto Broker
- SolidWorks
- Unity

### Communication

- MQTT-based temperature data communication
- Physical-to-virtual data transfer

## 8. AI / ML Model Details

### Linear Regression

Linear Regression is used to predict future temperature values based on historical temperature measurements.

The prediction system includes:

- One-step-ahead prediction
- Ten-step recursive prediction
- Adaptive historical window selection
- Prediction error evaluation using Mean Absolute Error

### Prediction Performance

Reported experimental results:

| Prediction Horizon | 10-Reading Window MAE | 80-Reading Window MAE |
|---|---:|---:|
| T+1 | 0.068 °C | 0.058 °C |
| T+10 | 0.544 °C | 0.395 °C |

The results indicate that prediction error increases with the forecast horizon.

### MQTT Anomaly Detection Study

The project documentation also discusses Random Forest, Decision Tree, and Isolation Forest for MQTT anomaly detection.

This study is distinct from the Linear Regression-based temperature prediction model.

## 9. System Architecture

The system follows the general data flow:

Physical Thermal Process  
↓  
DS18B20 Temperature Sensor  
↓  
ESP32 Data Acquisition  
↓  
Temperature Processing  
↓  
Linear Regression Prediction  
↓  
Future Temperature Forecast  
↓  
Threshold-Based Early Warning  
↓  
MQTT Communication  
↓  
Unity Digital Twin Visualization

The architecture diagram is available in:

`docs/Architecture_Diagram.pdf`

## 10. Experimental Results

The system acquires temperature readings at approximately 1.03-second intervals.

The experimental implementation demonstrates:

- Real-time temperature acquisition
- Future temperature prediction
- Prediction error calculation
- Threshold-based warning generation
- MQTT temperature data transmission
- 3D kettle model development

An experimental threshold of 85 °C was used to demonstrate early warning functionality.

The reported experiment generated a warning approximately 12 seconds before the actual temperature crossed the threshold.

The 85 °C threshold is an experimental value and is not an industrial safety limit.

## 11. Digital Twin Development

A 3D kettle model was developed using SolidWorks and imported into Unity.

The virtual model provides the foundation for representing the physical thermal process.

The project includes MQTT-based temperature communication.

Further development includes complete real-time synchronization, bidirectional communication, and closed-loop temperature control.

## 12. Demo Video

A 15–20 minute demonstration video is available here:

[Watch the Project Demo](YOUTUBE_UNLISTED_VIDEO_LINK)

## 13. Architecture Diagram

[View Architecture Diagram](docs/Architecture_Diagram.pdf)

## 14. Project Presentation

[View Project Presentation](docs/Project_Presentation.pdf)

## 15. Project Report

[View Project Report](docs/Project_Report_Phase1.pdf)

## 16. Open-Source License

This project is distributed under the MIT License.

See the LICENSE file for details.

## 17. Repository Structure

- `docs/` : Project report, architecture diagram, and presentation
- `firmware/` : ESP32 source code
- `digital-twin/` : Unity and SolidWorks project files
- `software/` : Prediction and MQTT software
- `data/` : Experimental dataset
- `results/` : Experimental graphs and analysis
- `images/` : Project photographs and screenshots

## 18. Future Work

- Improved machine learning-based prediction
- Complete physical-to-virtual synchronization
- Bidirectional communication
- Closed-loop temperature control
- Improved prediction accuracy
- Integration of intelligent control strategies

## 19. References

Refer to the bibliography provided in the project report.

## 20. Contact

For project-related information, refer to the team details provided above.
