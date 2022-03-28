#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

int BFS(int vertex_num, vector< pair< int, int > > adjacent_edge[], vector< int > &output){
    bool explored[vertex_num], repeat[vertex_num];
    for(int i=0;i<vertex_num;i++){
        explored[i] = false;
        repeat[i] = false;
    }
    int removed_weight = 0, source = 0;
    vector<int> Queue;
    explored[0] = true;
    Queue.push_back(0);
    while(!Queue.empty()){
        source = Queue.front();
        Queue.erase(Queue.begin());
        for(int i=0;i<adjacent_edge[source].size();i++){
            if(explored[adjacent_edge[source][i].first] == false){
                explored[adjacent_edge[source][i].first] = true;
                Queue.push_back(adjacent_edge[source][i].first);
            }
            else if(repeat[adjacent_edge[source][i].first] == false){
                removed_weight += 1;
                output.push_back(source);
                output.push_back(adjacent_edge[source][i].first);
                output.push_back(1);
            }
        }
        explored[source] = true;
        repeat[source] = true;
    }
    return removed_weight;
}

int MST_Prim(vector< int > &MST_set, int vertex_num, vector< pair< int, pair< int, int > > > edge_set, vector< pair< int, int > > adjacent_edge[], vector< int > &output){
    int removed_weight = 0, source = 0;
    bool explored[vertex_num];
    int key[vertex_num];
    int pi[vertex_num];
    for(int i=0;i<vertex_num;i++){
        explored[i] = false;
        key[i] = -INT8_MAX;
        pi[i] = -1;
    }
    key[source] = 0;
    priority_queue< pair< int, int > > max_heap;
    max_heap.push(make_pair(0, source));
    while(!max_heap.empty()){
        source = max_heap.top().second;
        explored[source] = true;
        max_heap.pop();
        for(int i=0;i<adjacent_edge[source].size();i++){
            if(explored[adjacent_edge[source][i].first] == false && key[adjacent_edge[source][i].first] < adjacent_edge[source][i].second){
                key[adjacent_edge[source][i].first] = adjacent_edge[source][i].second;
                max_heap.push(make_pair(key[adjacent_edge[source][i].first], adjacent_edge[source][i].first));
                pi[adjacent_edge[source][i].first] = source;
            }
        }
    }
    for(int i=0;i<edge_set.size();i++){
        if(pi[edge_set[i].second.first] != edge_set[i].second.second && pi[edge_set[i].second.second] != edge_set[i].second.first){
            removed_weight += edge_set[i].first;
            output.push_back(edge_set[i].second.first);
            output.push_back(edge_set[i].second.second);
            output.push_back(edge_set[i].first);
        }
        else{
            MST_set.push_back(edge_set[i].second.first);
            MST_set.push_back(edge_set[i].second.second);
            MST_set.push_back(edge_set[i].first);
        }
    }
    return removed_weight;
}

bool check(int u, int v, int vertex_num, bool discovered[], bool repeated[], vector< pair< int, int > > adjacent_edge[]){
    discovered[u] = true;
    for(int i=0;i<adjacent_edge[u].size();i++){
		if(adjacent_edge[u][i].first == v) return true;
        if(!discovered[adjacent_edge[u][i].first] && !repeated[adjacent_edge[u][i].first]){
            if(check(adjacent_edge[u][i].first, v, vertex_num, discovered, repeated, adjacent_edge)) return true;
        }
	}
	discovered[v] = true;
    repeated[v] = true;
    return false;
}

bool DFS(int u,int v, int vertex_num, vector< pair< int, int > > adjacent_edge[]){
    bool discovered[vertex_num];
    bool repeated[vertex_num];

    for(int i=0;i<vertex_num;i++){
        discovered[i] = false;
        repeated[i] = false;
	}
	return check(u, v, vertex_num, discovered, repeated, adjacent_edge);
}

int greedyFAS(int vertex_num, vector< pair< int, int > > who_in[], vector< pair< int, int > > who_out[], int in_deg[], int out_deg[], int delta[], vector< int > &output){
    vector< pair< int, int > > reference[vertex_num];
    for(int i=0;i<vertex_num;i++) reference[i] = who_out[i];
    int G_num = vertex_num;
    bool removed[vertex_num];
    for(int i=0;i<vertex_num;i++) removed[i] = false;
    int count = 0;
    int sink = 0;
    int source = 0;
    int del = 0;
    int temp_max = -INT8_MAX;
    vector< int > s1, s2;
    bool exist_sink = true;
    bool exist_source = true;
    while(G_num > 0){
        temp_max = -INT8_MAX;
        exist_sink = true;
        exist_source = true;
        while(exist_sink){
            for(int i=0;i<vertex_num;i++){
                if(out_deg[i] == 0){
                    sink = i;
                    in_deg[i] = -INT8_MAX;
                    out_deg[i] = -INT8_MAX;
                    removed[sink] = true;
                    break;
                }
                if(i==vertex_num-1) exist_sink = false;
            }
            if(exist_sink){
                for(int i=0;i<who_in[sink].size();i++){
                    if(!removed[who_in[sink][i].first]){
                        out_deg[who_in[sink][i].first] -= 1;
                        delta[who_in[sink][i].first] -= 1;
                    }
                }
                s2.insert(s2.begin(), sink);
                G_num -= 1;
            }
        }

        if(G_num <= 0) break;

        while(exist_source){
            for(int i=0;i<vertex_num;i++){
                if(in_deg[i] == 0){
                    source = i;
                    in_deg[i] = -INT8_MAX;
                    out_deg[i] = -INT8_MAX;
                    removed[source] = true;
                    break;
                }
                if(i==vertex_num-1) exist_source = false;
            }
            if(exist_source){
                for(int i=0;i<who_out[source].size();i++){
                    if(!removed[who_out[source][i].first]){
                        in_deg[who_out[source][i].first] -= 1;
                        delta[who_out[source][i].first] += 1;
                    }
                }
                s1.push_back(source);
                G_num -= 1;
            }
        }

        if(G_num <= 0) break;

        for(int i=0;i<vertex_num;i++){
            if(delta[i] > temp_max && !removed[i]){
                temp_max = delta[i];
                del = i;
            }
        }
        for(int i=0;i<who_out[del].size();i++){
            if(!removed[who_out[del][i].first]){
                in_deg[who_out[del][i].first] -= 1;
                delta[who_out[del][i].first] += 1;
            }
        }
        for(int i=0;i<who_in[del].size();i++){
            if(!removed[who_in[del][i].first]){
                out_deg[who_in[del][i].first] -= 1;
                delta[who_in[del][i].first] -= 1;
            }
        }
        s1.push_back(del);
        G_num -= 1;
        in_deg[del] = -INT8_MAX;
        out_deg[del] = -INT8_MAX;
        removed[del] = true;
    }
    int order[vertex_num];
    for(int i=0;i<vertex_num;i++){
        if(!s1.empty()){
            order[s1[0]] = i;
            s1.erase(s1.begin());
        }
        else{
            order[s2[0]] = i;
            s2.erase(s2.begin());
        }
    }
    for(int u=0;u<vertex_num;u++){
        for(int j=0;j<reference[u].size();j++){
            if(order[u] > order[reference[u][j].first]){
                count += reference[u][j].second;
                output.push_back(u);
                output.push_back(reference[u][j].first);
                output.push_back(reference[u][j].second);
            }
        }
    }
    return count;
}
///-------------------- MAIN --------------------///
int main(int argc, char* argv[]){

    /// command check start ///
    if(argc!=3){
        cout<<"please check again!";
        return 0;
    }
    /// command check end ///

    /// data preparation start ///
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    char direct_index = ' ';
    bool directed, weighted = false;
    fin >> direct_index;
    if(direct_index=='d') directed = true;
    int vertex_num = 0, edge_num = 0;
    fin >> vertex_num;
    fin >> edge_num;
    pair< int, pair< int, int > > edge_gen;
    vector< pair< int, pair< int, int > > > edge_set;
    vector< pair< int, int > > adjacent_edge[vertex_num];
    vector< pair< int, int > > who_out[vertex_num];
    vector< pair< int, int > > who_in[vertex_num];
    vector< int > temp_output = {};
    int temp_weight = 0;
    int in_deg[vertex_num];
    int out_deg[vertex_num];
    int delta[vertex_num];
    int u = 0, v = 0, weight = 0;

    if(directed){
        for(int i=0;i<vertex_num;i++){
            in_deg[i] = 0;
            out_deg[i] = 0;
            delta[i] = 0;
        }
    }

    for(int i=0;i<edge_num;i++){
        fin >> u >> v >> weight;
        if(weight!=1) weighted = true;
        edge_gen.first = weight;
        edge_gen.second.first = u;
        edge_gen.second.second = v;
        edge_set.push_back(edge_gen);
        adjacent_edge[u].push_back(make_pair(v, weight));
//        if(!directed) adjacent_edge[v].push_back(make_pair(u, weight));
        adjacent_edge[v].push_back(make_pair(u, weight));

//        else{
//            who_out[u].push_back(make_pair(v, weight));
//            who_in[v].push_back(make_pair(u, weight));
//            in_deg[v] += 1;
//            out_deg[u] += 1;
//            delta[v] -= 1;
//            delta[u] += 1;
//            for(int i=0;i<who_in[u].size();i++){
//                if(who_in[u][i].first == v){
//                    for(int j=0;j<who_out[v].size();j++){
//                        if(who_out[v][j].first == u){
//                            if(weight < who_in[u][i].second){
////                                fout << u << " " << v << " " << weight << endl;
//                                temp_output.push_back(u);
//                                temp_output.push_back(v);
//                                temp_output.push_back(weight);
//                                temp_weight += weight;
//                                who_out[u].erase(who_out[u].begin()+i, who_out[u].begin()+i+1);
//                                who_in[v].erase(who_in[v].begin()+j, who_in[v].begin()+j+1);
//                                in_deg[v] -= 1;
//                                out_deg[u] -= 1;
//                                delta[v] += 1;
//                                delta[u] -= 1;
//                            }
//                            else{
////                                fout << v << " " << u << " " << who_in[u][i].second << endl;
//                                temp_output.push_back(v);
//                                temp_output.push_back(u);
//                                temp_output.push_back(who_in[u][i].second);
//                                temp_weight += who_in[u][i].second;
//                                who_out[v].erase(who_out[v].begin()+j, who_out[v].begin()+j+1);
//                                who_in[u].erase(who_in[u].begin()+i, who_in[u].begin()+i+1);
//                                in_deg[u] -= 1;
//                                out_deg[v] -= 1;
//                                delta[u] += 1;
//                                delta[v] -= 1;
//                            }
//                            break;
//                        }
//                    }
//                }
//            }
//        }
    }
    /// data preparation end ///

    /// algorithm implementation start ///
    vector< int > output, MST_set;
    /// (1)unweighted & undirected / (2)weighted & undirected / (3)weighted & directed ///
    if(!weighted && !directed){
        ///(1) BFS
        fout << BFS(vertex_num, adjacent_edge, output) << endl;
        for(int i=0;i<output.size();i++){
            fout << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
            i = i + 2;
        }
    }
    else if(weighted && !directed){
        ///(2) MST by Prim's algorithm
        fout << MST_Prim(MST_set, vertex_num, edge_set, adjacent_edge, output) << endl;
        for(int i=0;i<output.size();i++){
            fout << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
            i = i + 2;
        }
    }
    else{
//        ///(3) greedyFAS
//        fout << greedyFAS(vertex_num, who_in, who_out, in_deg, out_deg, delta, output) + temp_weight << endl;
//        for(int i=0;i<output.size();i++){
//            fout << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
//            i = i + 2;
//        }
        ///(3) MST + DFS
        int MST_weight = MST_Prim(MST_set, vertex_num, edge_set, adjacent_edge, output);
        for(int i=0;i<output.size();i++){
//            fout << "output in MST" << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
            i = i + 2;
        }

        for(int i=0;i<MST_set.size();i++){
//            fout << "after running MST: " << MST_set[i] << " " << MST_set[i+1] << " " << MST_set[i+2] << endl;
            i = i + 2;
        }

        vector< pair< int, int > > MST_adj[vertex_num];
        vector< int > final_output;
        for(int i=0;i<MST_set.size();i++){
            MST_adj[MST_set[i]].push_back(make_pair(MST_set[i+1], MST_set[i+2]));
            i = i + 2;
        }

        for(int i=0;i<MST_set.size();i++){
//            fout<<"consider bi "<<MST_set[i]<<" "<<MST_set[i+1]<<" "<<MST_set[i+2]<<endl;
            for(int j=0;j<MST_adj[MST_set[i]].size();j++){
                for(int k=0;k<MST_adj[MST_set[i+1]].size();k++){
//                    cout<< "i "<<MST_set.size()<<" j "<<MST_adj[MST_set[i]].size()<<" k "<<MST_adj[MST_set[i+1]].size();
                    if(MST_adj[MST_set[i]][j].first == MST_set[i+1] && MST_adj[MST_set[i+1]][k].first == MST_set[i]){
//                        fout << "bi weight: " << MST_adj[MST_set[i]][j].second <<" " << MST_adj[MST_set[i+1]][k].second << endl;
                        if(MST_adj[MST_set[i]][j].second < MST_adj[MST_set[i+1]][k].second){
                            final_output.push_back(MST_set[i]);
                            final_output.push_back(MST_set[i+1]);
                            final_output.push_back(MST_adj[MST_set[i]][j].second);
//                            fout << "bidirect: " << MST_set[i] << " " << MST_set[i+1] << " " << MST_adj[MST_set[i]][j].second << endl;
                            MST_adj[MST_set[i]].erase(MST_adj[MST_set[i]].begin()+j);
                        }
                        else{
                            final_output.push_back(MST_set[i+1]);
                            final_output.push_back(MST_set[i]);
                            final_output.push_back(MST_adj[MST_set[i+1]][k].second);
//                            fout << "bidirect: " << MST_set[i+1] << " " << MST_set[i] << " " << MST_adj[MST_set[i+1]][k].second << endl;

                            MST_adj[MST_set[i+1]].erase(MST_adj[MST_set[i+1]].begin()+k);
                        }
                    }
                }
            }
            i = i + 2;
        }

        for(int i=0;i<output.size();i++){
//            fout << "i'm considered to be removed: " << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
			if(output[i+2]>0){
				if(DFS(output[i+1], output[i], vertex_num, MST_adj) == false){
					MST_adj[output[i]].push_back(make_pair(output[i+1], output[i+2]));
					MST_set.push_back(output[i]);
					MST_set.push_back(output[i+1]);
					MST_set.push_back(output[i+2]);
//                    fout << "push back to graph: " << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
				}
				else{
					final_output.push_back(output[i]);
					final_output.push_back(output[i+1]);
					final_output.push_back(output[i+2]);
//					fout << "removed: " << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
				}
			}
			else{
				final_output.push_back(output[i]);
				final_output.push_back(output[i+1]);
				final_output.push_back(output[i+2]);
//				fout << "removed: " << output[i] << " " << output[i+1] << " " << output[i+2] << endl;
			}
			i = i + 2;
		}

		int final_weight = 0;
		for(int i=0;i<final_output.size();i++){
            final_weight += final_output[i+2];
            i = i + 2;
        }

        fout << final_weight << endl;

		for(int i=0;i<final_output.size();i++){
            fout << final_output[i] << " " << final_output[i+1] << " " << final_output[i+2] << endl;
            i = i + 2;
        }

//        for(int i=0;i<temp_output.size();i++){
//            fout << temp_output[i] << " " << temp_output[i+1] << " " << temp_output[i+2] << endl;
//            i = i + 2;
//        }
//        fout<< "start" << endl;
//        int ccc = 0;
//        for(int i=0;i<MST_set.size();i++){
//            fout << MST_set[i] << " " << MST_set[i+1] << " " << MST_set[i+2] << endl;
//            i = i + 2;
//            ccc += 1;
//        }
//        fout << ccc <<endl;
    }
    /// algorithm implementation end ///

    fin.close();
    fout.close();
    return 0;
}
