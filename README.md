<p align="center">
  <img src="https://github.com/Simple-Robotics/proxsuite/raw/main/doc/images/proxsuite-logo.png" width="700" alt="Proxsuite Logo" align="center"/>
</p>

<p align="center">
  <a href="https://opensource.org/licenses/BSD-2-Clause"><img src="https://img.shields.io/badge/License-BSD%202--Clause-green.svg" alt="License"/></a>
  <a href="https://github.com/jcarpent/proxqp-unofficial/actions/workflows/ci-linux-osx-with-conda.yml"><img src="https://github.com/jcarpent/proxqp-unofficial/actions/workflows/ci-linux-osx-with-conda.yml/badge.svg" alt="CI - Linux/OSX/Windows - Conda"></a>
  <a href="https://badge.fury.io/py/proxsuite"><img src="https://badge.fury.io/py/proxsuite.svg" alt="PyPI version" height="20"></a>
</p>

**ProxSuite** is a collection of open-source, numerically robuste, precise and efficient numerical solvers (e.g., LPs, QPs, etc.) rooted on revisited primal-dual proximal algorithms.
While the first targeted application is Robotics, **ProxSuite** can be used in other contextes without any limits.
Through **ProxSuite**, we aim at offering to the community scalable optimizers which can deal with dense, sparse or matrix-free problems.

**ProxSuite** is actively developped and supported by the [Willow](https://www.di.ens.fr/willow/) and [Sierra](https://www.di.ens.fr/sierra/) research groups, joint research teams between [Inria](https://www.inria.fr/en), [École Normale Supérieure de Paris](https://www.ens.fr) and [Centre National de la Recherche Scientifique](https://www.cnrs.fr).

## Quick install

**ProxSuite** is distributed on many well-known package managers.

### With <img src="https://www.python.org/static/community_logos/python-logo-inkscape.svg" height="30" style="vertical-align: -1em;">:

```bash
   pip install proxsuite
```
This approach is only available on Linux and Mac OS X.

### With <img src="https://s3.amazonaws.com/conda-dev/conda_logo.svg" height="18">:

```bash
   conda install proxsuite -c conda-forge
```
This approach is available on Linux, Windows and Mac OS X.

### Alternative approaches

Alternative installation procedures are presented in the [Installation Procedure](#installation-procedure) section.

## ProxSuite main features

**Proxsuite** is fast:

   - C++ template library,
   - cache friendly.

**Proxsuite** is versatile, offering through a unified API advanced algorithms specialized for efficiently exploiting problem structures:

   - dense, sparse and matrix free matrix factorization backends,
   - advanced warm-starting options (e.g., equality-constrained initial guess, warm-start or cold-start options from previous results).

**Proxsuite** is flexible:

   - header only,
   - C++ 17/20 compliant,
   - Python and Julia bindings for easy code prototyping without sacrificing performances.

**Proxsuite** is extensible.
**Proxsuite** is reliable and extensively tested, showing the best performances on the hardest problems of the literature.
**Proxsuite** is supported and tested on Windows, Mac OS X, Unix and Linux.

## **ProxQP**

The **ProxQP** algorithm is a numerical optimization approach for solving quadratic programming problems of the form:

$$
\begin{align}
\min_{x} &  ~\frac{1}{2}x^{T}Hx+g^{T}x \\
\text{s.t.} & ~A x = b \\
& ~l \leq C x \leq u
\end{align}
$$

where $x \in \mathbb{R}^n$ is the optimization variable. The objective function is defined by a positive semidefinite matrix $H \in \mathcal{S}^n_+$ and a vector $g \in \mathbb{R}^n$. The linear constraints are defined by the equality-contraint matrix $A \in \mathbb{R}^{n_\text{eq} \times n}$ and the inequality-constraint matrix $C \in \mathbb{R}^{n_\text{in} \times n}$ and the vectors $b \in \mathbb{R}^{n_\text{eq}}$, $l \in \mathbb{R}^{n_\text{in}}$ and $u \in \mathbb{R}^{n_\text{in}}$ so that $b_i \in \mathbb{R},~ \forall i = 1,...,n_\text{eq}$ and $l_i \in \mathbb{R} \cup \{ -\infty \}$ and $u_i \in \mathbb{R} \cup \{ +\infty \}, ~\forall i = 1,...,n_\text{in}$.

### Citing **ProxQP**

If you are using **ProxQP** for your work, we encourage you to [cite the related paper](https://hal.inria.fr/hal-03683733/file/Yet_another_QP_solver_for_robotics_and_beyond.pdf/).

### Numerical benchmarks

The numerical benchmarks of **ProxQP** against other commercial and open-source solvers are available [here](https://github.com/Simple-Robotics/proxqp_benchmark).

For dense Convex Quadratic Programs with inequality and equality constraints, when asking for a relatively high accuracy (e.g., 1e-6), one obtains the following results.

<p align="center">
  <img src="https://github.com/Simple-Robotics/proxsuite/raw/main/doc/images/time_series_barplot_Random Mixed QP_dense_eps_abs_1e-6.jpg" width="600" alt="Random Mixed QP_dense_eps_abs_1e-6" align="center"/>
</p>

On the y-axis you can see timings in seconds, and on the x-axis dimension wrt to the primal variable of the random Quadratic problems generated (the number of constraints of the generated problem is half the size of its primal dimension). For every dimension, the problem is generated over different seeds and timings are obtained as averages over successive runs for the same problems. This chart shows for every benchmarked solvers and random Quadratic programs generated, barplots timings including median (as a dot) and minimal and maximal values obtained (defining the amplitude of the bar). You can see that **ProxQP** is always below over solvers, which means it is the quickest for this test.

For hard problems from the [Maros Meszaros testset](http://www.cuter.rl.ac.uk/Problems/marmes.shtml), when asking for a high accuracy (e.g., 1e-9), one obtains the results below.

<p align="center">
  <img src="https://github.com/Simple-Robotics/proxsuite/raw/main/doc/images/performance_profile_maros_meszaros_problems_high_accuracy.jpg" width="600" alt="maros_meszaros_problems_high_accuracy" align="center"/>
</p>

This chart above reports performance profiles of different solvers. It is classic for benchmarking solvers. Performance profiles correspond to the fraction of problems solved (on y-axis) as a function of certain runtime (on x-axis, measured in terms of a multiple of the runtime of the fastest solver for that problem). So the higher on the chart the better. You can see that **ProxQP** solves the quickest over 60% of the problems (i.e., for $\tau=1$), and that for solving about 90% of the problems, it is at most 2 times slower than the fastest solvers solving these problems (i.e., for $\tau\approx2$).

*Note: All these results have been obtained with a 11th Gen Intel(R) Core(TM) i7-11850H @ 2.50GHz CPU.*

## Installation procedure

Please follow the installation procedure [here](https://github.com/Simple-Robotics/proxsuite/blob/main/doc/5-installation.md).

## Documentation

The online **ProxSuite** documentation of the last release is available [here](https://simple-robotics.github.io/proxsuite/).
