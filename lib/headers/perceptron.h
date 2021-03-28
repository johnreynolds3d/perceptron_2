#ifndef perceptron_h
#define perceptron_h

struct TrainingSet {
  int inputs[2];
  int output;
};

struct TrainingSet *TrainingSet_create(int input_1, int input_2, int output);

void initialise_weights(int num_weights, double *weights, double *bias);

void train(int num_sets, struct TrainingSet **training_sets, int num_weights,
           double *weights, double *bias, double *total_error, int num_epochs);

double calc_dot_product_bias(int num_weights, double *weights, int num_inputs,
                             double *inputs, double *bias);

int calc_output(int num_weights, double *weights, double input_1,
                double input_2, double *bias);

void update_weights(struct TrainingSet **training_sets, int num_weights,
                    double *weights, double *bias, double *total_error, int j);

void TrainingSet_print(struct TrainingSet *training_set);

void TrainingSet_destroy(struct TrainingSet *training_set);

#endif
