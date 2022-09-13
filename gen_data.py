#!/usr/bin/env python3

from subprocess import check_output
import numpy as np

sizes = ["100", "200"]
lengths = ["300", "600", "800"]
corrs = [str(n).zfill(3) for n in list(range(1, 11))]
# thresholds = ["0.75", "0.80", "0.85"]

threshold = "0.85"
alpha = "0.75"


def main():
    print("instance,det_fitness_avg,det_fitness_std,det_time_avg,det_time_std,rnd_fitness_avg,rnd_fitness_std,rnd_time_avg,rnd_time_std")

    for size in sizes:
        for length in lengths:
            det_metrics = np.array([])
            det_times = np.array([])
            rnd_metrics = np.array([])
            rnd_times = np.array([])

            for corr in corrs:
                det_metric, det_time = str(check_output(
                    ["./build/greedy",  "-i", f"dataset/{size}-{length}-{corr}.txt", "-th", f"{threshold}"])).split(",")
                rnd_metric, rnd_time = str(check_output(
                    ["./build/greedy_rnd", "-i", f"dataset/{size}-{length}-{corr}.txt", "-th", f"{threshold}", "-a", alpha])).split(",")

                det_metric = det_metric[2:]
                det_time = det_time[:-3]
                rnd_metric = rnd_metric[2:]
                rnd_time = rnd_time[:-3]

                det_metrics = np.append(det_metrics, int(det_metric))
                det_times = np.append(det_times, float(det_time))
                rnd_metrics = np.append(rnd_metrics, int(rnd_metric))
                rnd_times = np.append(rnd_times, float(rnd_time))

            print(
                f"{size}-{length},{np.average(det_metrics)},{np.std(det_metrics)},{np.average(det_times)},{np.std(det_times)},{np.average(rnd_metrics)},{np.std(rnd_metrics)},{np.average(rnd_times)},{np.std(rnd_times)}")


if __name__ == "__main__":
    main()
