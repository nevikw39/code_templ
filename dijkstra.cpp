void dijkstra(int n, const vector<vector<pair<int, int>>> &g, int s, vector<int64_t> &d)
{
    _heap<pair<int64_t, int>> pq;
    vector<decltype(pq)::point_iterator> itrs(n);
    itrs[s] = pq.push({d[s] = 0, s});
    while (pq.size())
    {
        int t = pq.top().ND;
        pq.pop();
        itrs[t] = nullptr;
        for (const auto &[i, w] : g[t])
            if (d[i] > d[t] + w)
            {
                if (itrs[i])
                    pq.modify(itrs[i], {d[i] = d[t] + w, i});
                else
                    itrs[i] = pq.push({d[i] = d[t] + w, i});
            }
    }
}
