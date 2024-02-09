# ProjectM
 
# 2024 / 02 / 07
- Dynamic Camera 구현
    - 마우스 위치에 따른 Spring Arm 의 Socket Offset 조절로 카메라 위치 수정
    - FInterp 를 통해 카메라 움직임 속도 조절

# 02 / 09
- FindLookAtRotation
    - ```FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(StartLocation,TargetLocation)``` 을 통해 Start 에서 Target 을 바라보기 위한 Rotator 값을 구할 수 있음
- Orient Rotation
    - True 일 경우, Actor 움직임에 따라 Actor 가 자동으로 회전
    - Character Movement Component 에 정의되어 있음
    - 해당 옵션을 False 로 해도 움직임이 이상한 경우, 고정된 카메라에서 Actor 의 움직임을 확인하고 버그를 수정하기
