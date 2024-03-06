# ROS2 Header Map

A feature full, lightweight library meant to ease the pain of converting high level memory rich ROS2 environments into the lower level resource constrained MicroController world via micro-ros(which is based on eProsima's Micro XRCE-DDS)

This library has **first** a focus on being easy to work with on the microcontroller of choice, which as of now corresponds to the RA8M1 from Renesas, being memory resilient is also a secondary focus followed by flexibility, this is due to work hour equivalence, an hour of new code on the pc may correspond to 10+ hours on the microcontroller specially due to how dynamic allocation occurs, lack of user-space, tight memory, less widely used CPU architecture's and finally weird compiler/linker settings which take time to address and fix. **It will be presumed that if it "werks on my microcontroller" it will most likely work on whatever architecture is chosen for the computer**, however some kind of Unit Testing may be implemented in the future.

## General Specs/Layout

### Atomic Data
Every message **should** derive from a atomic data type, in this case one that excludes strings, complex data structures, arrays, etc... **TL;DR**: try to stick to numeric messages such as Integer-based or Float-based.
### Bilateral Conversion between ROS2 and Plain C
Every message **should** be able to be easily converted from ROS2 back to C via structures or at least raw memory, this is to facilitate the process of developing logic and algorithms.
### Template Based/External Store dependant
To avoid lengthy code try to abstract most data structures, ie lets say you have some flags that fit onto a byte, instead of creating logic exclusively for it create both a a generic Logic Class that handles some correction/ conversion and then create a context specific structure or an enum.

So basically like so:
```c++
enum EBS_pressure_state{...}
enum Datalink_WOL_state{...}

class wrapper_states{...}

```

then on an external store or whatever pattern you wanna use you would do something like:

```c++
wrapper_states<EBS_pressure_state> curr_ebs;
/*Some distant code*/
wrapper_states<Datalink_WOL_state> curr_wol;
```

### Complexity/Smartness from Simple/Dumb Components
Due to limitations from the microcontroller try to collapse Topics that share a wider context when taking algorithms/logic/processing into account. For example you shouldn't agregate everything to DriveTrain, Eletronics or Autonomous Systems, but avoid sending 30 different flags all relating to emergency states. This is because micro-ROS is somewhat recent, and latency seems to be an issue. **NOTE: Latency, Throughput and Bandwidth are all different concepts**

### Standard oriented, Adding Overhead
Although your free to add your own structs, classes, etc... everything that is to be exchanged by the ACU and PC must be standardized and must not deviate from a set standard. This is to avoid seemingly easy implementable features to last 3 months since development iterations between the eletronics department and the Autonomous Driving department are not in sync. **So yes changing a unit may only take you 5 seconds, but the other party might have to change various files, all with different variables and validations. Then theres also updating hardware which tipically takes forever, and lastly theres also the widely known fact that changing suddenly/often causes a [giant loss of productivity](https://www.atlassian.com/blog/productivity/why-context-switching-ruins-productivity).**  

#### Overhead
**Yes, the standard may seem stupid or counterintuitive**, but even if it would facilitate everyone to just use a certain unit, if another was decided to be standardized, "too bad", this makes it so that the standard is portable between vehicles, pipelines and hardware. If theres a thing thats guaranteed: is that no piece of hardware, firmware or software is final, even at the last week before the competition. Specially when you add Autonomous Driving into the mix

