//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_HITTABLELIST_H
#define RAY_TRACING_HITTABLELIST_H

#include <vector>
#include "hittable.h"

class hittableList: public hittable{
public:
    std::vector<shared_ptr<hittable>> objList;

    hittableList(){}
    hittableList(shared_ptr<hittable> object){ add(object);}

    void clear(){objList.clear();}

    void add(shared_ptr<hittable> obj){
        objList.push_back(obj);
    }

    bool hit(const ray& r, interval r_t, hitRecord& rec) const override{
        hitRecord tmp_rec;
        bool hit_anything = false;
        auto closest = r_t.max;

        for(const auto& object: objList){
            if(object->hit(r, interval(r_t.min, closest), tmp_rec)){
                hit_anything = true;
                closest = tmp_rec.t;
                rec = tmp_rec;
            }
        }
        return hit_anything;
    }
};
#endif //RAY_TRACING_HITTABLELIST_H
