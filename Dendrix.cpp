#include "Dendrix.h"

int main(int argc,char* argv[])
{
    list<string> genes;
    DictStringSet gene_mutatedSamples;
    ifstream     sample_mut_f;
    ifstream     analyzed_genes_file;
    int K;
    int mAS_perGene;
    int num_iterations;
    set<string> all_samples;
    DictStringSet sample_mutatedGenes;
    int num_exper;
    int step_length;
    string sampleID;

    if(argc < 8)
        {
            cout << "Usage: python Dendrix.py mutations_file K minFreqGene number_iterations analyzed_genes_file num_exper step_length\n";
            cout << "mutations_file: input file with mutation matrix (see README.txt for description)\n";
            cout << "K: size of the sets to be sampled\n";
            cout << "minFreqGene: minimum frequency of mutation for a gene to be considered in the analysis\n";
            cout << "number_iterations: number of iterations of the MCMC\n";
            cout << "analyzed_genes_file: file with list of analyzed genes (see README.txt for description)\n";
            cout << "num_exper: number of times the experiment is going to be run (see README.txt for description)\n";
            cout << "step_length: number of iterations of the MCMC between two samples\n";
            exit(0);
        }

    genes.clear();
    gene_mutatedSamples.clear();
    sample_mut_f.open(argv[1]);
    K = atoi(argv[2]);
    mAS_perGene = atoi(argv[3]);
    num_iterations = atoi(argv[4]);
    analyzed_genes_file.open(argv[5]);
    all_samples.clear();
    sample_mutatedGenes.clear();
    num_exper = atoi(argv[6]);
    step_length = atoi(argv[7]);

    printf("Load genes...\n");

    string line;
    list<string> v;
    
    while(!analyzed_genes_file.eof())
        {
	    getline(analyzed_genes_file,line);
	    lsplit(line,v);
	    if(!v.empty())
		{
		    genes.push_back(v.front());
		    gene_mutatedSamples[v.front()] = set<string>();
		}
       	    v.clear();
        }
    //    genes.pop_back();
    gene_mutatedSamples.erase("");
    analyzed_genes_file.close();
    
    printf("Loading Mutations...\n");

    vector<string> vv;

    while(!sample_mut_f.eof())
	{
	    getline(sample_mut_f,line);
	    if(line.empty())
		break;
	    vsplit(line,vv);
	    sampleID = vv[0];
	    all_samples.insert(sampleID);
	    sample_mutatedGenes[sampleID] = set<string>();
	    
	    for (int i = 0; i < (sz(vv) - 1); ++i)
		{
		    string gene = vv[i+1];
		    
		    if(cpresent(genes,gene))
			{
			    if(!present(gene_mutatedSamples,gene))
				gene_mutatedSamples[gene] = set<string>();
			    gene_mutatedSamples[gene].insert(sampleID);
			    sample_mutatedGenes[sampleID].insert(gene);
			}
		}
	    vv.clear();
	}
    
    sample_mut_f.close();
    
    DictStringDouble sample_numMut;
    
    tr(sample_mutatedGenes,it)
	{
	    // it->first refers to the sampleID or PatientID
	    unsigned tmp_numMut = sample_mutatedGenes[it->first].size();
	    sample_numMut[it->first] = (double)tmp_numMut;
	    
	}
    
    set<string> genes_toRemove;
    
    tr(gene_mutatedSamples,it)
	{
	    // here it->first refers to gene
	    if(gene_mutatedSamples[it->first].size() < mAS_perGene)
		genes_toRemove.insert(it->first);
	}
    
    tr(genes_toRemove,it)
	{
	    //*it is a gene
	    gene_mutatedSamples.erase(*it);
	    genes.erase(find(all(genes),*it));
	}
    
    printf("Number of genes:%u\n",genes.size());
       
    printf("Cleaning sample_mutatedGenes Table...\n");
    
    tr(sample_mutatedGenes,it)
	{
	    //here it->first refers to sampleID
	    tr(genes_toRemove,gene)
		{
		    if(present(sample_mutatedGenes[it->first] ,*gene))
			sample_mutatedGenes[it->first].erase(*gene);
		}
	    
	}
    
    /* main algo starts here */ 
    list<string>solution;
    string to_exchange;
    set<string> next_solution;

    for (int exp_n = 0; exp_n < num_exper; ++exp_n)
       	{
	    random_samples(genes,K,solution);
	    set<string> genes_set(all(genes));
	    int avg = 0;
	    DictSetInt num_visits;
	    
	    for (int itera = 0; itera < num_iterations; ++itera)
		{
		    string next_gene = random_sample_sel(genes_set);
		    
		    if(cpresent(solution,next_gene))
		       to_exchange = next_gene;
		    else
			{
			    list<string> s;
			    random_samples(solution,1,s);
			    to_exchange = s.front();
			}
		    list<string> to_exchangeList;
		    list<string> next_geneList;
		    
		    to_exchangeList.push_back(to_exchange);
		    next_geneList.push_back(next_gene);
		    
		    set<string> solution_Set ;
		    solution_Set = convertListToSet(solution); 
		    
		    set<string> to_exchange_Set;
		    to_exchange_Set = convertListToSet(to_exchangeList);
		    
		    set<string> next_gene_Set;
		    next_gene_Set = convertListToSet(next_geneList);
		    
		    set_difference(all(solution_Set),all(to_exchange_Set),inserter(next_solution,next_solution.end()));	   
		    set_union(all(next_solution),all(next_gene_Set),inserter(next_solution,next_solution.end()));
		    
		    double expon = measure(next_solution,solution_Set,sample_mutatedGenes);
		    
		    double prob = min(1.0,exp(expon));
		    double coin = random01();
			
		    if(coin <= prob)
			solution_Set = next_solution;

		}
	}
    return 0;
}
