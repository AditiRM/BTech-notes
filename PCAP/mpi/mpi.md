---                                                                                    
title: "PCAP : MPI Cluster"
author: Aditi Rajendra Medhane 111803177
---

## MPI Cluster- Library of routines to perform parallelism by using more than one CPU at a time

#### GOAL : To achieve parallelism with network of nodes in LAN. 

**MPICH** is a widely-used implementation of MPI.
- Install MPICH on all the machines.

## Steps:

### 1. **Host file comfiguration**:
   How to access MPI – 
   Message Passing Interfaces other nodes by giving it some name instead of using  
   IP addresses by mapping IP address to some name for easy access
   ---
   $ cat /etc/host
   [Map the ip with name]
   ---

### 2. **Creating new user**
   Making new user for easy configurations.
   ---
   $ sudo adduser mpiuser
   ---

### 3. **Install and setup ssh**
   For communications within network/nodes, we have to set up ssh.
   
   $ sudo apt-get install openssh-server
   $su - mpiuser
   
   **Keys Generation**
   
   $ ssh-keygen-t dsa
   
   **Adding the keys to all nodes for easier login in other machines/nodes:**
   
   $ ssh-copy-id worker <node name>
   This will set up a secure communication between the nodes
   To enable passwordless ssh ->
   
   $eval ssh-agent
   $ ssh-add-/.ssh/id_dsa
   
   **For login**
   $ssh worker

### 4. Install and set up NFS (Network file sharing/sharing data between machines)
   NFS, a protocol that allows you to share directories and files over a  network.
   
   - install 
   - Making a new directory
   
   $ mkdir cloud
   $ sudo apt-get install nfs-kemel-server
   
   - create a directory
 
   - export cloud
   $ cat /etc/exports
   -add  
   /home/mpiuser/cloud "(rw, sync, no_root_squash,no_subtree_check)
   $ exportfs-a
   
   - restart nfs server if required
   
   $ sudo service nfs-kemel-server restart

   Nfs-worker
   install packages
   
   $ sudo apt-get install nfs-common
   $mkdir cloud
   $ sudo mount -t nfs manager :/home/mpiuser/cloud-/cloud

   - check
   $df-h
   
   - To make mount permanent
   $ cat /etc/fstab
   
   - add entry

### 5. Run MPI programs
   - compile
   
   $mpicc-o mpi_sample mpi_sample.c 
   
   - copy the compiled program to shared directory 
 
   $ cd cloud
   To run it on own machine

   $ mpirun-np 2 ./cpi 
   
   - To run it within a cluster,
   $mpirun -np 5-hosts worker, localhost ./cpi
   
   
