#ifndef DELYNOI_CONFIG_H
#define DELYNOI_CONFIG_H

class DelynoiConfig {
private:
    int circle_discretization_grade;
    double double_comparison_tolerance;
    int scale_for_clipper;

    static DelynoiConfig* s_instance;

    DelynoiConfig();
    DelynoiConfig(const DelynoiConfig& other) = delete;
    DelynoiConfig& operator=(const DelynoiConfig& copy) = delete;
public:
    void setDiscretizationGrade(int d);
    void setTolerance(double t);
    void setScale(int s);

    int getDiscretizationGrade();
    double getTolerance();
    int getScale();

    static DelynoiConfig* instance();
};


#endif 
