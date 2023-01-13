

#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

#include "config.h"
#ifdef USE_OPENMP
	#include <omp.h>
#endif


using namespace std;
bool bReevaluate = false;
#include "gravitationunivIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;

CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;

#define STD_TPL


// No user functions.


// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 21 "gravitationuniv.ez"




for (int i=0;i<NB_SAMP;i++) { // for all samples

	double t = globalRandomGenerator->random(0., 2. * pi * i / NB_SAMP); 
    float x_earth, y_earth;
	x_earth = a * cos(t) - a * e;
	y_earth = a * sqrt(1 - e*e) * sin(t);
	
	sample[i][0] = t;
	sample[i][1] = x_earth;
	sample[i][2] = y_earth;
	
	float F = 1e18*(G*M_earth*M_sun)/((x_earth)*(x_earth)+(y_earth)*(y_earth));
	sample[i][3] = F;
}
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 41 "gravitationuniv.ez"
  // typically to write the results in a file

printf("Constantes à retrouver: \n");
printf("M_earth = %e ; M_sun = %e  ; constante_gravitationelle = %e  \n", M_earth, M_sun ,g );
printf("Constantes trouvées: \n");
printf("M_earth = %e ; M_sun = %e  ; constante_gravitationelle = %e  \n", ((IndividualImpl*)bBest)->mass_earth, ((IndividualImpl*)bBest)->mass_sun, ((IndividualImpl*)bBest)->constante_grav);
}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void gravitationunivInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void gravitationunivFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 124 "gravitationuniv.ez"

// No at beginning of generation function.

}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	
// No at end of generation function.

}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	
// No generation function.

}


IndividualImpl::IndividualImpl() : CIndividual() {
   
  // Genome Initialiser
#line 58 "gravitationuniv.ez"


(*this).mass_sun = globalRandomGenerator->random(0.99,1.01);  //mass of sun 
(*this).mass_earth = globalRandomGenerator->random(1e-5, 1e+8); //mass of earth
(*this).constante_grav = globalRandomGenerator->random(6.67e-12, 6.69e-10); //gravitational constant
    

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    #line 77 "gravitationuniv.ez"

float fScore=0;
for (int i=0;i<NB_SAMP;i++) {

  float x_earth = sample[i][0];
  float y_earth = sample[i][1];
  float F = 1e18*((*this).constante_grav*(*this).mass_earth*(*this).mass_sun)/((x_earth)*(x_earth)+(y_earth)*(y_earth));
  fScore+=abs(F-sample[i][3]);
}
return fitness =  fScore;

  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.

}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	EASEA_Line << this->constante_grav << " ";
	EASEA_Line << this->mass_sun << " ";
	EASEA_Line << this->mass_earth << " ";

    EASEA_Line  << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	EASEA_Line >> this->constante_grav;
	EASEA_Line >> this->mass_sun;
	EASEA_Line >> this->mass_earth;

    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    constante_grav=genome.constante_grav;
    mass_sun=genome.mass_sun;
    mass_earth=genome.mass_earth;



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part
  	#line 66 "gravitationuniv.ez"

float fLocus = globalRandomGenerator->random(0.0, 1.0);
if (fLocus < 0.33) child.mass_earth = parent2.mass_earth;
if (fLocus < 0.66 && fLocus >= 0.33) child.mass_sun = parent2.mass_sun;
if (fLocus >= 0.66) child.constante_grav = parent2.constante_grav;



	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	
}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


void IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
  #line 73 "gravitationuniv.ez"



}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = true;
	this->nbGen = setVariable("nbGen",(int)30);
	this->nbCPUThreads = setVariable("nbCPUThreads", 1);
        this->isLogg = setVariable("isLogg", 1);
	this->reevaluateImmigrants = setVariable("reevaluateImmigrants", 0);

	omp_set_num_threads(this->nbCPUThreads);
	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Tournament"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)2.000000);
	replacementPressure = setVariable("reduceFinalPressure",(float)2.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)2.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)2.000000);
	pCrossover = 1.000000;
	pMutation = 1.000000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)10000);
	offspringPopulationSize = setVariable("nbOffspring",(int)10000);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)1.000000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)1.000000));

	this->elitSize = setVariable("elite",(int)1);
	this->strongElitism = setVariable("eliteType",(int)1);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)30));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",0);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",1);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",0);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"gravitationuniv";
	this->plotOutputFilename = (char*)"gravitationuniv.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",0);
	std::string* ipFilename=new std::string();
	*ipFilename=setVariable("ipFile","ip.txt");

	this->ipFile =(char*)ipFilename->c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.300000);
    this->serverPort = setVariable("serverPort",2929);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	//EZ_NB_GEN = (unsigned*)setVariable("nbGen",30);
	EZ_current_generation=0;
  EZ_POP_SIZE = parentPopulationSize;
  OFFSPRING_SIZE = offspringPopulationSize;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("gravitationuniv.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}
