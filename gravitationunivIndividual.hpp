

#ifndef PROBLEM_DEP_H
#define PROBLEM_DEP_H

//#include "CRandomGenerator.h"
#include <stdlib.h>
#include <iostream>
#include <CIndividual.h>
#include <Parameters.h>
#include <cstring>
#include <sstream>

using namespace std;

class CRandomGenerator;
class CSelectionOperator;
class CGenerationalCriterion;
class CEvolutionaryAlgorithm;
class CPopulation;
class Parameters;

extern int EZ_POP_SIZE;
extern int OFFSPRING_SIZE;

// User declarations
#line 7 "gravitationuniv.ez"

#define NB_SAMP 1000 // number of samples
static float sample[NB_SAMP][4]; // 3 for time, y position of earth and y position of sun and force

#define G 6.67430e-11 // gravitational constant
#define M_earth 5.972e24 // mass of earth
#define M_sun 1.989e30 //mass of sun
#define V_earth 29.78e3 // velocity of earth at perihelion
#define r_perihelion 1.471e11 // distance between sun and earth at perihelion
const double pi = 3.14159265358979323846;
const double a = 149.6e6; // distance moyenne entre la Terre et le Soleil en km
const double e = 0.0167;  // excentricité de l'orbite de la Terre



// User classes


class IndividualImpl : public CIndividual {

public: // in gravitationuniv the genome is public (for user functions,...)
	// Class members
  	// Class members 
  float distance_earth_sun;
  float speed_earth_sun;
  float mass_sun;
  float mass_earth;


public:
	IndividualImpl();
	IndividualImpl(const IndividualImpl& indiv);
	virtual ~IndividualImpl();
	float evaluate();
	static unsigned getCrossoverArrity(){ return 2; }
	float getFitness(){ return this->fitness; }
	CIndividual* crossover(CIndividual** p2);
	void printOn(std::ostream& O) const;
	CIndividual* clone();

	void mutate(float pMutationPerGene);

	void boundChecking();      

	string serialize();
	void deserialize(string EASEA_Line);

	friend std::ostream& operator << (std::ostream& O, const IndividualImpl& B) ;
	void initRandomGenerator(CRandomGenerator* rg){ IndividualImpl::rg = rg;}

};


class ParametersImpl : public Parameters {
public:
	void setDefaultParameters(int argc, char** argv);
	CEvolutionaryAlgorithm* newEvolutionaryAlgorithm();
};

/**
 * @TODO ces functions devraient s'appeler weierstrassInit, weierstrassFinal etc... (en gros gravitationunivFinal dans le tpl).
 *
 */

void gravitationunivInit(int argc, char** argv);
void gravitationunivFinal(CPopulation* pop);
void gravitationunivBeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void gravitationunivEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void gravitationunivGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm);


class EvolutionaryAlgorithmImpl: public CEvolutionaryAlgorithm {
public:
	EvolutionaryAlgorithmImpl(Parameters* params);
	virtual ~EvolutionaryAlgorithmImpl();
	void initializeParentPopulation();
};

#endif /* PROBLEM_DEP_H */


