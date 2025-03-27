#include <bits/stdc++.h>

using namespace std;

class GraphAlgorithm{
    private:
        int N;
        vector<vector<int>> graph;
        vector<vector<int>> reversegraph;
        vector<int> indegree;

    public:
        GraphAlgorithm() {}

        GraphAlgorithm(int N_){
            N = N_;
            graph.resize(N);
            reversegraph.resize(N);
            indegree.assign(N, 0);
        }

        GraphAlgorithm(vector<vector<int>>& graph_, vector<vector<int>> reversegraph_, vector<int>& indegree_){
            N = (int) indegree_.size();
            graph = graph_;
            reversegraph = reversegraph_;
            indegree = indegree_;
        }

        GraphAlgorithm(vector<vector<int>>& graph_){
            N = (int) graph_.size();
            graph = graph_;
            reversegraph.resize(N);
            indegree.assign(N, 0);
        }

        virtual void Query(vector<vector<int>>& graph){}


        vector<vector<int>>& get_graph(){
            return graph;
        }

        vector<vector<int>>& get_reversegraph(){
            return reversegraph;
        }

        vector<int>& get_indegree(){
            return indegree;
        }
};



class isCycle : public GraphAlgorithm{
    private:

    public:
        isCycle() : GraphAlgorithm(){} 


        void Query(GraphAlgorithm& graph_, bool& yes){
            vector<vector<int>> graph = graph_.get_graph();
            int N = graph.size();

            vector<char> color(N, 'W');

            function<void(int,int)> dfs = [&](int u, int v) -> void {
                color[u] = 'G';

                for(auto x : graph[u]){
                    if(color[x] == 'G') yes = true;
                    else if(color[x] == 'W') dfs(x, u);
                }

                color[u] = 'B';
            };

            for(int i = 0 ; i < N ; i++){
                if(color[i] == 'W') dfs(i, -1);
                if(yes) return;
            }

            return;
        }

};



class validOrder : public GraphAlgorithm{
    private:

    public:
        validOrder() : GraphAlgorithm(){}
        

        void Query(GraphAlgorithm& graph_, vector<int>& topsort, bool& yes){
            vector<vector<int>>& graph = graph_.get_graph();
            vector<int> indegree = graph_.get_indegree();
            int N = graph.size();

            priority_queue<int, vector<int>, greater<int>> pq;

            for(int i = 0 ; i < N ; i++){
                if(indegree[i] == 0) pq.push(i);
            }

            while(!pq.empty()){
                int source = pq.top();
                pq.pop();
                topsort.push_back(source);


                for(auto x : graph[source]){
                    indegree[x]--;
                    if(indegree[x] == 0) pq.push(x);
                }
            }

            if((int)topsort.size() != N){
                yes = true;
                return;
            }
        }
};


class indepComponent : public GraphAlgorithm{
    private:
        vector<vector<int>> SCC;

    public:
        indepComponent() : GraphAlgorithm(){}

        void dfs(int u,  vector<vector<int>>& graph, vector<bool>& vis, vector<int>& component){
            if(vis[u]) return;
            vis[u] = true;
            component.push_back(u);

            for(auto x : graph[u]){
                dfs(x, graph, vis, component);
            }
            
        }

        void toposort(int u, vector<vector<int>>& graph, vector<bool>& vis, vector<int>& topsort){
            if(vis[u]) return;
            vis[u] = true;

            for(auto x : graph[u]){
                toposort(x, graph, vis, topsort);
            }

            topsort.push_back(u);
        }


        void Query(GraphAlgorithm& graph_, bool yes = true){
            vector<vector<int>> graph = graph_.get_graph();
            vector<int> topsort;

            
            int N = graph.size();
            vector<bool> vis(N, false);
            vector<bool> vis1(N, false);

            for(int i = 0 ; i < N ; i++){
                if(!vis1[i]) toposort(i, graph, vis1, topsort);
            }
            
            vector<vector<int>>& reversegraph = graph_.get_reversegraph();
            reverse(topsort.begin(), topsort.end());
            
            int count = 0;
            int mx = INT_MIN;

            for(auto x : topsort){
                if(!vis[x]){
                    vector<int> component;
                    dfs(x, reversegraph, vis, component);
                    mx = max(mx, (int)component.size());
                    count++;
                    SCC.push_back(component);
                }
            }

            if(yes) cout << count << " " << mx << endl;
        }

        vector<vector<int>>& get_SCC(){
            return SCC;
        }

};



class maxHype : public GraphAlgorithm{
    private:

    public:
        maxHype() : GraphAlgorithm(){}
        void Query(GraphAlgorithm& graph_, vector<int>& H){

            vector<vector<int>>& graph = graph_.get_graph();
            int N = graph.size();
            set<pair<int,int>> edges;

            for(int i = 0 ; i < N ; i++){
                if(!graph[i].size()) continue;
                for(auto x : graph[i]) edges.insert({i, x});
            }  

            indepComponent components;
            components.Query(graph_, false);

            vector<vector<int>> SCC = components.get_SCC();

            int numComp = SCC.size();

            vector<int> hype(numComp);

            for(int i = 0 ; i < numComp ; i++){
                int sum = 0;
                for(auto y : SCC[i]){
                    sum += H[y];
                }
                hype[i] = sum;
            }

            vector<vector<int>> CondensedGraph(numComp);

            for(int i = 0 ; i < numComp ; i++){
                vector<int> comp1 = SCC[i];
                for(int j = 0 ; j < numComp ; j++){
                    if(i == j) continue;

                    vector<int> comp2 = SCC[j];
                    bool yes = false;
                    for(auto x : comp1){
                        for(auto y : comp2){
                            if(edges.find({x,y}) != edges.end()){
                                yes = true;
                                CondensedGraph[i].push_back(j);
                                break;
                            }
                        }
                        if(yes) break;
                    }
                }
            }


            GraphAlgorithm GSCC(CondensedGraph);

            vector<int> maxhype(numComp);

            for(int i = 0 ; i < numComp ; i++){
                maxhype[i] = hype[i];
            }

            validOrder valid;
            bool yes = false;
            vector<int> topsort;
            valid.Query(GSCC, topsort, yes);

            for(auto i : topsort){
                for(auto x : CondensedGraph[i]){
                    maxhype[x] = max(maxhype[x], maxhype[i] + hype[x]);
                }
            }

            cout << *max_element(maxhype.begin(),maxhype.end()) << endl;
        }
};


class Comparator{
    private:
        bool flag;
    public:
        Comparator(bool flag_){
            flag = flag_;
        }

        bool operator () (int a, int b){
            return flag ? a < b : a > b;
        }
};



int main(){
    int N, M;
    cin >> N >> M;

    vector<int> H(N);
    for(int i = 0 ; i < N ; i++) cin >> H[i];

    vector<vector<int>> graph(N);
    vector<vector<int>> reversegraph(N);
    vector<int> indegree(N);

    for(int i = 0 ; i < M ; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        reversegraph[v].push_back(u);
        indegree[v]++;
    }            

    GraphAlgorithm graph_(graph, reversegraph, indegree);

    int Q;
    cin >> Q;

    while(Q--){
        int type;
        cin >> type;

        if(type == 1){
            isCycle check;
            bool yes = false;
            check.Query(graph_, yes);
            if(yes) cout << "YES" << endl;
            else cout << "NO" << endl;
        }

        else if(type == 2){
            indepComponent SCC;
            SCC.Query(graph_);
        }

        else if(type == 3){

            bool yes = false;
            validOrder valid;
            vector<int> topsort;
            valid.Query(graph_, topsort, yes);
               
            
            if(!yes){
                for(auto x : topsort){
                    cout << x + 1 << " ";
                }
                cout << endl;
            }
            else cout << "NO" << endl;
        }

        else{
            maxHype max;
            max.Query(graph_, H);
        }
    }

    return 0;
}