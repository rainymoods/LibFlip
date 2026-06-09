# Artifacts for IEEE S&P 2027

The artifacts for the paper "Undermining Multimodal Perception in Autonomous Driving Systems via Shared Library Fault Injection", submitted to IEEE S&P 2027.

## 1. Structural Overview

According to Appendix B, this repository includes the following source code and evaluation results:

* `AppAnalyzer/`: Implements the In-vehicle Application Analysis Module (§4.2) and the CAN Traffic Translation Module (§4.4).
* `AutoTrigger/`: Implements the Dynamic Command Trigger Module (§4.3).
* `RealWorldPOC/`: Contains the verification scripts for the Remote Real-time Vehicle Status Eavesdropping (§6.1) and Malicious Vehicle Control Commands Injection (§6.2).
* `Results/`: Aggregates the raw statistical telemetry and log files for the CAN reverse engineering and traffic hijacking benchmarks.
* `TrafficCollector/`: Contains the low-level firmware utilities for sniffing CAN messages from physical pinouts and decoding the captured traffic.

## 2. Dependency and Environment Specifications

### 2.1 Hardware Requirements
* Intercepted IVI hardware or a validated target emulation testbed (for RealWorldPOC execution).
* Standard CAN-to-USB interface hardware (for TrafficCollector deployment).

### 2.2 Software Prerequisites
The static analysis component requires the following standard toolchains:
* Oracle Java Development Kit (JDK 11)
* Android Software Development Kit (SDK, API Level 32)

## 3. Step-by-Step Replication Guidance

### 3.1 Component: AppAnalyzer
Goal: To ingest target IVI applications, perform backward program slicing, and correlate application-level invocation logs with concurrent CAN traffic sequences.

1. Parameter Configuration: Update the static properties in `com/ivihunter/SootConfig.java` to define the baseline paths for the targeted APK inputs.
2. Execution: Compile and execute the main pipeline entry point by invoking: `com/ivihunter/main/Main.java`.