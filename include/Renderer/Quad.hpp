//
// Created by Oles Gedz on 11/06/2020.
//

#ifndef FT_VOX_INCLUDE_QUAD_HPP_
#define FT_VOX_INCLUDE_QUAD_HPP_
#include "Entity.hpp"
#include "Model.hpp"

class Quad : public Entity {
 public:
  Quad();
  const Model& getModel() const;
 private:
  Model m_model;
};
#endif //FT_VOX_INCLUDE_QUAD_HPP_
