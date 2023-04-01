# Abstract
- Euclidean Distance Map과 Voronoi Diagram을 GridMap을 이용해서 업데이트하는 방법을 소개
- brushfire algorithm의 동적인 다양화를 차용해서 환경 변화로 인해 영향을 받은 셀을 업데이트함.
- GridStep보다는 Actual Euclidean Distance를 적용
- 오픈소스로 올라와 있음

# Introduction
- GVD(Generalized Voronoi Diagram)은 다양한 영역에서 활용되는 자료구조
- 로보틱스에서는 Navigation 문제를 풀어내는 유명한 셀 분해 방법으로 활용됨
- GVD는 자유 영역의 점들의 집합이며, 이 점들은 가장 가까운 장애물과의 거리가 동일합니다.
- 따라서, 이는 Path Planning에서 RoadMap으로 사용됩니다.
- GVD는 GVD 상에 있는 다른 경로들이 장애물에 대해 위상적으로 다른 경로에 해당한다는 점에서 희소합니다. (? 뭔소리임?)
- 
