#ifndef EVENTS_HPP
#define EVENTS_HPP

#pragma once

template<typename Type>
void getMouse(Type::*method_name)(), void* object){
    (static_cast<Type*>(object)->*method_name());
}


void check(){
    getMouse();
}

#endif