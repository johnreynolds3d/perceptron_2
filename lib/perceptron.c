#include "headers/perceptron.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrainingSet *TrainingSet_create(int input_1, int input_2, int output) {

  struct TrainingSet *training_set = malloc(sizeof(struct TrainingSet));
  assert(training_set != NULL);

  training_set->inputs[0] = input_1;
  training_set->inputs[1] = input_2;
  training_set->output = output;

  return training_set;
}

void TrainingSet_destroy(struct TrainingSet *training_set) {
  assert(training_set != NULL);
  free(training_set);
}

void TrainingSet_print(struct TrainingSet *training_set) {
  printf("\t[%d %d] %d\n", training_set->inputs[0], training_set->inputs[1],
         training_set->output);
}

void initialise_weights(int num_weights, double *weights, double *bias) {

  for (int i = 0; i < num_weights; i++) {
    weights[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
  }

  *bias = (double)rand() / RAND_MAX * 2.0 - 1.0;
}

double calc_dot_product_bias(int num_weights, double *weights, int num_inputs,
                             double *inputs, double *bias) {

  assert(weights != NULL);
  assert(inputs != NULL);

  assert(num_weights == num_inputs);

  double dot_product_bias = 0;

  for (int i = 0; i < num_weights; i++) {
    dot_product_bias = dot_product_bias + (weights[i] * inputs[i]);
  }

  dot_product_bias = dot_product_bias + *bias;

  return dot_product_bias;
}

int calc_output(int num_weights, double *weights, double input_1,
                double input_2, double *bias) {

  double inputs[] = {input_1, input_2};
  double dot_product_bias =
      calc_dot_product_bias(num_weights, weights, 2, inputs, bias);

  return (dot_product_bias > 0) ? 1 : 0;
}

void update_weights(struct TrainingSet **training_sets, int num_weights,
                    double *weights, double *bias, double *total_error, int j) {

  double error = training_sets[j]->output -
                 calc_output(num_weights, weights, training_sets[j]->inputs[0],
                             training_sets[j]->inputs[1], bias);

  *total_error = *total_error + fabs(error);

  for (int i = 0; i < num_weights; i++) {
    weights[i] = weights[i] + (error * training_sets[j]->inputs[i]);
  }

  *bias = *bias + error;
}

void train(int num_training_sets, struct TrainingSet **training_sets,
           int num_weights, double *weights, double *bias, double *total_error,
           int num_epochs) {

  printf("I start out by setting my weights and bias to random numbers between "
         "-1 and 1:\n\n");

  initialise_weights(num_weights, weights, bias);

  printf("\tWeights: %9f  %9f    Bias: %9f\n\nThen the training begins...\n\n",
         weights[0], weights[1], *bias);

  for (int i = 0; i < num_epochs; i++) {

    printf("\tEpoch %d:\n", i + 1);

    *total_error = 0;

    for (int j = 0; j < num_training_sets; j++) {

      update_weights(training_sets, num_weights, weights, bias, total_error, j);

      printf("\tWeights: %9f  %9f    Bias: %9f\n", weights[0], weights[1],
             *bias);
    }

    printf("\tTotal Error: %d\n\n", (int)*total_error);
  }
}
