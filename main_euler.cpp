#include <math.h>
#include <stdio.h>

const int MAX_ATOMS = 3;

using namespace std;

int main(){
  int num_atom_chain = 3; // number of atoms in the chain
  double k = 1; // Force constant
  double particle_mass = 1; // mass of one particle_mass
  double time_step = 0.01; // time step
  double print_interval = 0.2; // time interval between printing
  double sim_len = 20; // Simulation length
  double num_t_steps = 10; // number of time steps between printing
  double force_vect[MAX_ATOMS]; // the force vector
  double pos_vect[MAX_ATOMS]; //position vector
  double velocity_vect[MAX_ATOMS]; // velocity vector

  double ZERO = 0.0;

  // Calculate number of integration steps & print freq

  double integration_steps = floor( (sim_len/time_step) + 0.5);
  double print_freq = floor( (print_interval/time_step) + 0.5);

  // Setting the initial position and velocities of the each aprticle in the chain
  //particle one
  pos_vect[0] = 1.0;
  velocity_vect[0] = 0.0;

  //particle two
  pos_vect[1] = 0.0;
  velocity_vect[1] = 0.0;

  //particle three
  pos_vect[2] = -1.0;
  velocity_vect[2] = 0.0;


  // Print header

  printf( " Time          Atom #         Position\n" );
  printf( "____________________________________\n\n" )  ;

  // Lets begin the integration
  for(int j=0; j< integration_steps; j++){
    //compute right neighbour forces
    for (int i=0; i<num_atom_chain-1;i++){
      force_vect[i] = pos_vect[i+1] - pos_vect[i];
    }
    force_vect[num_atom_chain-1] = ZERO;
    //addition of left neighbour forces
    for(int i=1; i<num_atom_chain;i++){
      force_vect[i] = force_vect[i] + pos_vect[i-1] - pos_vect[i];
    }
    //advance position and velocity
    for(int i=0; i<num_atom_chain; i++){
      pos_vect[i] = pos_vect[i] + time_step*velocity_vect[i];
      velocity_vect[i] = velocity_vect[i] + time_step*k*force_vect[i]/particle_mass;
    }
    // print results
    if (fmod((j+1), print_freq) == 0){
      for(int i=0;i<num_atom_chain;i++){
        printf("%11.4E %3d  % 17.10E\n", (j+1)*time_step, i+1, pos_vect[i]);
      }
    }
  }
  return 0;
}
