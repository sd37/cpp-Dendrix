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
    
    printf("Loading Mutations...");

    vector<string> vv;

    while(!sample_mut_f.eof())
	{
	    string gene;
	    getline(sample_mut_f,line);
	    vsplit(line,vv);
	    sampleID = vv[0];
	    all_samples.insert(sampleID);
	    sample_mutatedGenes[sampleID] = set<string>();
	    
	    for (int i = 0; i < (sz(vv) - 1); ++i)
		{
		    gene = vv[i+1];
		    
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
    return 0;
}
