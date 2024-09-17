- [Virtualization](#virtualization)
  - [Hypervisors](#hypervisors)
  - [Memory Virtualization](#memory-virtualization)
  - [CPU Virtualization](#cpu-virtualization)
  - [IO Virtualization](#io-virtualization)
  - [More Details on Hypervisors](#more-details-on-hypervisors)
  - [The Intel Vt-x Instruction Set](#the-intel-vt-x-instruction-set)
  - [The Quick Emulator](#the-quick-emulator)
  - [Creating a VM using KVM module](#creating-a-vm-using-kvm-module)
  - [Vhost-Based Data communication](#vhost-based-data-communication)
  - [Alternative Virtualization Mechanism](#alternative-virtualization-mechanism)
  - [Uni-kernels - Minimal OS Interface](#uni-kernels---minimal-os-interface)
  - [Project Dune - Get rid of OS interface and run process in Ring 0](#project-dune---get-rid-of-os-interface-and-run-process-in-ring-0)
  - [NOVM - Optimizing booting aspect](#novm---optimizing-booting-aspect)
  - [HotPlug Module](#hotplug-module)
  - [Namespaces](#namespaces)
  - [Namespace Types](#namespace-types)
  - [CGroups](#cgroups)
  - [What is KVM(Kernel Virtual Machine), QEmu(Quick Emulator), libvirt, virtio, virtqueues ?](#what-is-kvmkernel-virtual-machine-qemuquick-emulator-libvirt-virtio-virtqueues-)


## Virtualization

<aside>
📌 An abstraction on top of the actual resource we want to virtualize
</aside>

There are two class of virtualization

- **VM Based Virtualization**
    - Virtualize the complete OS
    - The abstraction it present is in the form of virtual devices like virtual disk, virtual CPUs, and virtual NICs
    - This virtualize the complete ISA
- **Container Based Virtualization**
    - This form don’t abstract the hardware, but uses techniques within Linux kernel to isolate access paths from different resources
    - Logical boundary within in the same OS
    - A separate root file system, a separate process tree, a separate network subsystem, and so on

### Hypervisors

<aside>
💡 Software which virtualize OS, called as the hypervisor

</aside>

Two parts

- **Virtual Machine Monitor (VMM)**
    - Used for trap-and-emulate the privileged instruction set
    - This traps all privileged access; interrupts; network calls;
    - The VMM has to satisfy three properties by Popek and Goldberg (1973)
        - **Isolation**
            - Should isolate guests (VMs) from each other
        - **Equivalency**
            - Should behave same with or without virtualization
        - **Performance**
            - Reduce the overhead of using VM.
- **Device Model**
    - Used for virtualizing the I/O devices

### Memory Virtualization

- Guest should never know it is not controlling physical memory
- Guest should never we able to control physical memory
- There are three memory abstraction involved when running a guest OS
    - **Guest Virtual Memory** - Guest process view
    - **Guest Physical Memory** - Guest OS view
    - **System Physical Memory** - VMM view
- There are two possible approaches to handle this
    - **Shadow page table** (software technique)
        - Direct mapping from Guest Virtual Memory → System Physical Memory
        - More performant, because no extra layer of translation
        - Drawback
            - Any change in shadow page table, need to be trapped.
            - VMM handle the changes (by trap-and-emulate)
                - How ? - By making shadow page table (guest page table) as read-only
                - Any attempt by Guest OS to write to them causes a trap and the VMM can update the shadow tables
    - **Nested Page Table** with Hardware Support (hardware technique)
        - Extended Page Tables (EPT) - Intel and AMD provides a solution to this problem via hardware extension. Intel provides - EPT, which allow the MMU to walk two page tables
        - The first walk is from the guest virtual memory to guest physical memory; and second walk is from guest physical memory to system physical memory
        - So all translation now happen through the hardware, there is no need to maintain shadow page table
        - Guest page table are maintained by guest OS, and other page table are maintained by VMM (hypervisor)
        
        <aside>
        📌 Main issue is the flush of cache or TLB (translation look-aside buffer) [part of MMU], cache need to be flushed on a context switch, this is bringing up another VM. But in EPT, the hardware introduces a VM identifier via the address space identifier, which means the TLB cache can have mapping for different VMs at the same time, which is performance booster
        
        </aside>
        

### CPU Virtualization

- Protection rings built into the x86 architecture
- This rings allow CPU to protect memory and control privileges and determine what code execute at what privilege level
- The kernel code runs in the most privilege mode, Ring 0, and the use space used for running processes runs in Ring 3
- Hardware required to be in Ring 0 before running any privilege instruction
- If any attempt is made to run privilege instruction in Ring 3, then a fault is generate by CPU
- The kernel has registered fault handlers and, based on the fault type, a fault handler is invoked
- In case of VM-based virtualization, if the fault is not handled, the whole VM could be killed
- All privilege instruction execution from Ring 3 is controlled by a code segment register via the code privilege level (CPL) bit. All calls from Ring 3 are gated to Ring 0.
- The same concept is applied in virtualized OS. Guest OS is allocated Ring 1 and guest process in Ring 3. The VMM runs in Ring 0. Any privileged instruction has to be trapped and emulated
- VMM traps - privilege and sensitive instructions
- Older version of x86 CPUs are not virtualizable, which means not all sensitive instruction are privileged. Instruction like SGDT, SIDT, and more can be executed in Ring 1 without being trapped. So thus not safe. To solve this problem
    - Binary translation in case of full virtualization
        - No changes are made to the Guest OS
        - Instructions are trapped and emulated for the target environment. But this cause a lot of performance overhead, as lot of instruction need to be trapped into host/hypervisor and emulated
    - Para virtualization in case of XEN with hyper calls
        - Here we make the guest os knows that it is virtualized (loosening one of the 3 rules)
        - This avoid excessive trapping to the host
        - Device drivers code is changed, and split into two parts
            - Front end - open to the guest OS (guest device drivers)
            - Back end - with the hypervisor (host device drivers)
        - The guest and host drivers now communicate over ring buffers
        - Ring buffer is allocated from the guest memory
        - Now guest can accumulate data into the ring buffer and make one *hypercall* (also called as kick) to signal that the data is ready to drained. This avoid excessive traps from the guest to the host and is a performance win
    
    <aside>
    📌 In 2005, x86 finally became virtualizable. Intel introduces one more ring, called Ring-1, which is also called VMX root mode (Virtual Machine Extension). The VMM runs in VMX mode and the guest run in non-root mode
    
    </aside>
    
    - This means now guest can run in Ring 0 of VMX mode and, for the majority of the instruction there is no trap.
    - Privilege and sensitive instruction that guests need are executed by the VMM in root mode via the trap
    - These switches are called VM Exists (i.e., the VMM takes over instruction execution from the guest) and VM Entries
    - This virtualizable CPU also manages a data structure called VMCS (VM control structure) and it has state of VM and registers
    - The CPU uses this information during the VM Entries and Exists
    - The VMCS is like task_struct, the data structure used to represents a process. One VMCS pointer points to the current active VMCS. When there is a trap, VMCS process the state of all guest registers, like the reason of exists, and so on
    - Advantages with hardware-assisted virtualization are two-folds
        - No binary translation
        - No OS modification
    - The main problem is VM Exit and Entry, which required lot of CPU cycles

### IO Virtualization

[Notes IITB - Prof. Mythilli](https://www.cse.iitb.ac.in/~mythili/teaching/cs695_spring2021/slides_pdf/07-iovirt.pdf)

There are two mode of IO virtualization

- Full virtualization
    - Guest OS is unaware of virtualization
    - Each I/O get trap to hypervisor and hypervisor perform I/O on the physical device
- Para virtualization
    - In this case guest OS is made aware of that it is virtualized
    - Special drivers are loaded in guest OS for I/O. The **system calls** for I/O are replaced by **hyper calls** 
      - This replacement is important so that optimization on I/O can be performed
    - Guest side drivers are called as the *front-end drivers* and host side drivers are called as the *back-end drivers*
    - Front-end is designed based on virtio standards. Virtio is the virtualization standard for implementing para-virtualization 
      - Virtio-net, vertio-block are some of the devices which QEmu supports

> Virtio is the virtualization standard for implementing para-virtualization


- The back-end drivers can work in two ways
    - They can use QEMU emulation, QEMU emulates the system calls. This means that the hypervisor lets the user-space QEMU program make the actual device calls
    - They can use mechanism like vhost, where QEMU emulation is avoided and the hypervisor kernel make the actual device call
- The communication between front-end and back-end is done by virtqueue abstraction. The virtqueue presents an API to interact with, which allows it to enqueue and dequeue buffer. Depending on driver type, the driver can use zero or more queues. In case of network virtqueue on queue is for request and other to receive the packets
- Guest Initiate network packet write via guest kernel → virtio device in the guest take those buffer and put in virtqueue → back end of the virtqueue is the worker thread, receive the buffer (or guest can use `eventfd` for telling back-end) → Buffer are then written to the tap device file descriptor. The tap device is connected via software bridge (Linux Bridge) → other side of bridge is physical interface

<aside>
📌 So hardware industry is catching up with the virtualization, CPU with more rings and instruction with vt-x or be it memory - Extended Page Table

</aside>

- IO are virtualized using IO-MMU
- SRIOV - Single root I/O virtualization - allows SRIOV compatible devices to be broken into multiple virtual functions

### More Details on Hypervisors

- Components - KVM and QEMU
- Linux provides use of QEMU in user-space and a specialized kernel module called the KVM (the linux Kernel Virtual Machine). The KVM uses Intel vt-x extension instruction set to isolate resources at the hardware level

### The Intel Vt-x Instruction Set

Intel’s virtualization technology 

- Vt-x : For Intel x86 IA-32 and 64-bit architecture
- Vt-i  : For Itanium processor
- In VM, the program instruction are translated twice, first to virtual CPU instruction and then to physical CPU instruction
- Thus we have vt-x feature (kind of dedicated CPU)
- This vt-x also solves the problem where by x86 instruction architecture cannot be virtualized
- Now guest os run in ring 0 of vt-x mode
- This reduce trap and emulation
- Also the sensitive instruction which earlier were not trapped, now can be configured to get trap to the VMM which is running Ring-1
- The guest OS itself can’t handle I/O calls, so it delegates them to the VMM(Ring -1)

### The Quick Emulator

- QEMU runs in Ring 3(user process). It uses vt-x to provide guest with an isolated environment
- QEMU owns the Guest RAM
- Virtual CPU are scheduled on physical CPU
- QEMU can use para virtualized devices like virtio to provide guest with the virtio devices
- **Virtio-blk** for block devices and **virtio-net** for network devices
- QEMU dedicates separate thread for the I/O. This thread runs an event loop, which means they are non-blocking
- For I/O it registered file descriptor

![Untitled](images/Untitled.png)

### Creating a VM using KVM module

- ioctl commands are made to the kernel KVM module, which exposes a /dev/kvm device to the guest

### Vhost-Based Data communication

- When vhost is used for data communication then QEMU is out of data plane
- Direct communication between guest and host
- The QEMU stays in the control plane, where it setup the vhost devices on the kernel using ioctl commands

![Untitled](images/Untitled%201.png)

- When the device /net/vhost-net is initialized, a kernel thread is allocated
- The thread handle IO from a specific guest
- The thread listens to the event on the host side, on the virtqueue
- When an event arrives to drain the data, the I/O thread drain the packet from the tx(transmission) queue of the guest
- The thread then transmit this data to the tap device, which make it available to the underlying bridge
- The KVM kernel module register the `eventfd` for the guest.
- The FD is registered against the kick, which drains the data
- An `eventfd` is an IPC offers a wait-notify facility between user-space program and kernel or vise-versa
- FD are not only limited for files. We can also have FD for the event. These FD then exposes mechanism like `poll`, `select` and `epoll` . The mechanism can then facilitate a notification system when those FD are written to
- The consumer thread can be made to wait on an `epoll` object via `epoll_wait`. Once producer thread writes to the FD, the epoll mechanism will notify the consumer of the event ( 1 Edge trigger - as soon as event is detected, instant or 2) level triggered - when event is present)
- `ioeventfd` to send data from guest to host. `irqfd` to receive interrupt from the host to guest
- Similarly guest can also register to changes in FD
- The guest driver can listen for those changes
- An interrupt is generated to the guest when rx buffer is full via `irqfd` . From the host the thread which are associated with the tap devices redirect this data to the right buffers.

### Alternative Virtualization Mechanism

Namespace and c-group based mechanism that Docker uses

- This reduces the interface exposed by different software layer like VMM and reduces attack vectors - through memory exploitation and getting higher privileges
- Use hardware isolation to isolate different component

But this class is weaker as compared to VMM (or VM based approach)

We want to bring these two worlds closer

### Uni-kernels - Minimal OS Interface

Art of making a minimalistic OS (or library OS)

- This means that if an application only require network API, why to bundle keyboard, mouse devices ?

### Project Dune - Get rid of OS interface and run process in Ring 0

Technically we are not limited to only run guest OS after using isolation provided by vt-x on the memory and CPU

- So instead of an OS, Dune spins simply an Linux process
- This means the process is now suppose to run in Ring-0 of the CPU and has the machine interface exposed to it. The process can be made to sandbox by
    - Running the trusted code of a process in Ring 0.
    - Running the untrusted code in Ring 3
- To bootstrap the process, Dune creates an operating environment, which entails setting up the page table (CR3). Setup IDT

![Untitled](images/Untitled%202.png)

### NOVM - Optimizing booting aspect

- Type of hardware container (an alternative form of virtualization)
- Uses KVM APIs to create the VM by using `/dev/kvm` device file
- Instead of presenting a disk interface to the VM, no vm present a file system (9p) interface to VM
- No BIOS, VMM simply put into 32 bit protected mode directly, thus save time

<aside>
💡 Web Assembly (Wasm) is leading innovation in this space. Wasm module, within the same process (the WASM runtime). Each module is isolated from other module, so we get sandboxing per tenant. This will prevent cold start and leading forward towards serverless computer paradigm

</aside>

### HotPlug Module

- Dynamically resize block devices and RAM allocated to the Guest without restarting the guest

### Namespaces

- Linux container or also called as Linux Namespaces
- Allow kernel to isolate - mount points, network subsystem among processes scoped for different namespaces
- Today container are the de-facto of the cloud industry.
- Container provides faster spin-up time and have less overhead than VM
- VM based emulates the hardware and provides an OS as the abstraction. Bulk of OS code and the device drivers are loaded as part of provisioning
- But container virtualize the OS itself

<aside>
💡 Linux container are made of Linux kernel primitives

- Linux namespaces
- Cgroups
- Layered File System
</aside>

- A namespace is a *data structure* which provides *logical isolation* within in the Linux Kernel
- A namespace controls the visibility
- Sandboxing is achieved using namespaces

### Namespace Types

- **UTS** - Allow a process to see different hostname than global
- **PID** - Separate process tree, but as a subtree of host processes
- **Mount**
    - All the mount points a process can see
    - If a process within a namespace, it can only see mount within that namespace
    - A mount in the kernel is represented by data structure called `vfsmount`
    - Whenever a mount operation invoked, a `vfsmount` structure is created and the *dentry* of the mount point as well as the *dentry* of the mounted tree are populated.
    - Dentry is a data structure maps inode → filename
    - Apart from mount, there is *bind mount,* which allows a directory to mount instead a device at the mount point
    - Container works on the concept of bind mount
    - When a volume is created for a container, it’s actually a bind mount of a directory within the host to mount point within the container file systems
- **Network**
    - Separate network subsystem
    - Different routes, iptables, network interfaces
- **IPC**
    - POSIX message queue between two processes in the same namespace, if different namespace then it will block
- **Cgroups**
    - stands for Control Groups
    - A group of processes with similar resource constraint
    - This namespace restrict the visibility
- **Time**
    - Change the date and time in a container
    - Adjust the clocks for a container restored from a checkpoint

### CGroups

- Namespace restricting the visibility. But is that good enough for virtualization ?
- Any process in a namespace can still hog the actual physical resources - like running an infinite loop or forking a lot of process such that consuming the RAM
- Thus we need something more to control the resources
- This is achieved by using control groups
- Cgroups works on the concept of the cgroup controllers and are represented by a file system ***cgroupfs*** in the Linux kernel
- First we need to mount the cgroup file system at /sys/fs/cgroups

### What is KVM(Kernel Virtual Machine), QEmu(Quick Emulator), libvirt, virtio, virtqueues ? 

- Both KVM and QEmu are hypervisors (or VMM)
  - KVM is Type-1 hypervisor (kernel space)
  - QEmu is Type-2 hypervisor (user space)
- Qemu is designed to work as standalone 
  - Qemu provides supports to fully emulate peripheral devices, memory and cpu.
  - Qemu works on the principle of binary-translation (if no h/w support)
- KVM on the other hand provide hardware-assisted virtualization (helping hand to the virtualization software like QEmu)
  - Build-in CPU virtualization(VT-x, AMDv) to reduce overhead like cache, I/O, memory 
- How do KVM and QEmu talks ? 
  - KVM exposes a dummy device to the QEmu (/dev/kvm)
- Qemu with KVM can be leveraged to run virtual machines near native speed by leveraging hardware extension like VT-x by Intel, AMDv by AMD
  - With KVM, Qemu can just create a VM with vCPUs that the processor is aware of, that runs native-speed instructions
  - When a special instruction is reached by KVM, like device interaction/memory touch, vCPU pauses and inform QEMU of the cause of the pause, allowing hypervisor to react on that event 

- Libvirt is an interface which translate XML-formatted configuration to qemu CLI calls 
  - Command line tool - virsh

- The Virtio Specification: devices and drivers
  - Consider it as an interface(or protocol), which every OS/environment should agree; 
  - Devices and Drivers
    - Hypervisor expose the virtio devices to the guest (through transport method)
      - Most common transport method is PCI or PCIe bus 
      - Or in some case devices can be available at some predefined guest's memory addresses (MMIO). 
      - These devices can be fully virtual (which mean no physical device at all)
    - By design these devices looks like a physical device to the guest
  - Control plane (front end)
    - Negotiation b/w host and guest for establishing and terminating the data plane (setup for backend)
  - Data plane (back end) 
    - Used to send actual data (packets) b/w host and guest
  
    
- KQemu 
  - In special case when source and target are same architecture (like x86 on x86)
  - It still has to parse the code and remove any 'priviledge instruction' and replace them with the context switches 
  
- KVM (kernel Virtual Machine)
  - Linux kernel module 
  - This switches the processor into a new **guest** state
  - The guest state has its own set of ring states, but privileded ring0 instruction fall back to the hypervisor code
  - Since it is a new processor mode of execution, the code does't have to modify in any way 
  - Apart from processor state switching, the kernel module also handle a few low-level parts of emulation like the MMU registers 
  - KVM is fork of the Qemu executable (Goal is Qemu should work every where, but if there is KVM module available then it could automatically used that)
  - The kvm-qemu executable works like normal Qemu: allocates RAM, loads the code, and instead of recompiling it, or calling KQemu, it spawns a thread (this is important). 
  - The thread calls the KVM kernel module to switch to guest mode and proceeds to execute the VM code.
  - On a privileged instruction, it switches back to the KVM kernel module, which, if necessary, signals the Qemu thread to handle most of the hardware emulation.
  
> When working together, KVM arbitrates access to the CPU and memory, and QEMU emulates the hardware resources (hard disk, video, USB, etc.). When working alone, QEMU emulates both CPU and hardware. KVM is to accelerate it if the CPU has VT enabled. Libvirt provides a daemon and client to manipulate VMs for convenience.

- Ref: [Stack Exchange](https://serverfault.com/questions/208693/difference-between-kvm-and-qemu)