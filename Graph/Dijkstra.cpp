//Dijkstra by GNeos :v

ll d[N];
#define INF (1LL << 60)
vector <pii> graph[N];

//Shortest Path from s:

void dijkstra(int s){
    for(int j=0; j<N; j++) d[j] = INF;
    d[s] = 0;
    priority_queue <pii,vector < pii > ,greater < pii > > q;
    q.push({0,s});
    while(!q.empty()){
        int d_v = q.top().first;
        int v = q.top().second;
        q.pop();
        if(d_v != d[v]) continue;
        for(auto u:graph[v]){
            int to = u.first;
            int d_to = u.second;
            if(d[v] + d_to < d[to]){
                d[to] = d[v] + d_to;
                q.push({d[to],to});
            }
        }
    }
}
