// author - sonaspy@outlook.com
// coding - utf_8

#ifndef __HUFFMAN__
#define __HUFFMAN__
#include "bintree.h"
namespace dsa
{
typedef unordered_map<char, int> FREQ_table;
class huffman : public bintree<char>
{
protected:
    struct _cmp
    {
        bool operator()(const binode<char> *a, const binode<char> *b) const { return a->freq > b->freq; }
    };
    int _wpl;
    priority_queue<binode<char> *, vector<binode<char> *>, _cmp> _pq;

public:
    huffman(FREQ_table &mp)
    {
        _wpl = -1;
        binode<char> *v, *w, *root;
        for (auto &kv : mp)
        {
            v = new binode<char>(kv.first);
            v->freq = kv.second;
            _pq.push(v);
        }
        while (_pq.size() > 1)
        {
            v = _pq.top(), _pq.pop();
            w = _pq.top(), _pq.pop();
            root = new binode<char>(0255, v, w);
            v->parent = w->parent = root;
            root->freq = v->freq + w->freq;
            _wpl += root->freq;
            _pq.push(root);
        }
        this->__update_root(root);
    }
    inline void clear()
    {
        bintree<char>::clear();
        _wpl = -1;
    }
    int wpl()
    {
        return _wpl;
    }
    ~huffman() { this->clear(); }
};
} // namespace dsa
#endif