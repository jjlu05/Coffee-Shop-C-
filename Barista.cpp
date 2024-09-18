#include "Barista.h"

Barista::Barista() : ID(-1), is_busy(0), task_start(-1), task_duration(-1), free_time(0) {}

Barista::Barista(int id, int busy, int start, int duration, int free) 
    : ID(id), is_busy(busy), task_start(start), task_duration(duration), free_time(free) {}

void Barista::setID(int id) {
    ID = id;
}

void Barista::setBusy(int busy) {
    is_busy = busy;
}

void Barista::setStart(int start) {
    task_start = start;
}

void Barista::setDuration(int duration) {
    task_duration = duration;
}

void Barista::setFreeTime(int free) {
    free_time = free;
}

void Barista::increaseFree() {
    ++free_time;
}

void Barista::printBarista() {

    cout <<ID <<" " << is_busy << " " << task_start << " " << task_duration << " " << free_time<<endl;
}

int Barista::getBusy() {
    return is_busy;
}

int Barista::getStart() {
    return task_start;
}

int Barista::getDuration() {
    return task_duration;
}

int Barista::getFreeTime() {
    return free_time;
}

int Barista::getID() {
    return ID;
}

ostream& operator<<(ostream& out, Barista b) {
    out << b.ID << " " << b.is_busy << " " << b.task_start << " " << b.task_duration << " " << b.free_time;
    return out;
}
