

std::vector< std::vector<double> > dijkstra = {
    {0,2,8,4,-1,-1,-1},
    {2,0,-1,-1,3,-1,-1},
    {8,-1,0,-1,2,3,-1},
    {4,-1,-1,0,-1,8,-1},
    {-1,3,2,-1,0,-1,9},
    {-1,-1,3,8,-1,0,3},
    {-1,-1,-1,-1,9,3,0}
};

 /* 地点間の距離が格納されている二次元配列Distance[i][j] */
  /* ※1 地点iと地点jが同一の地点の場合は0が格納されている */
  /* ※2 地点iと地点jが隣接地点でない場合は-1が格納されている */
  
  int nPoint=N;/* 地点の数 */
  int sp;/* 出発地の地点番号 */
  int dp;/* 目的地の地点番号 */
  
  printf("出発地の地点番号を入力してください ==> ");
  scanf("%d",&sp);
  
  printf("目的地の地点番号を入力してください ==> ");
  scanf("%d",&dp);
  
  /* 出力変数sRouteとsDistを定義 */
  int sRoute[nPoint];/* 出発地から目的地までの最短経路上の地点の地点番号を目的地から出発地の順に設定する1次元配列 */
  int sDist;/* 出発地から目的地までの最短距離 */
  
  /* その他使う変数 */
  int pDist[nPoint];/* 出発地から各地点までの最短距離を設定する配列 */
  int pRoute[nPoint];
  bool pFixed[nPoint];/* 出発地から各地点までの最短距離が確定しているかどうかを識別するための配列 */
  int sPoint,i,j,newDist;
  
  sDist=99999; /* 出発地から目的地までの最短距離に初期値を格納する（変更しなくてよい） */
  
  for(i=0;i<nPoint;i++){
    sRoute[i]=-1; /* 最短経路上の地点の地点番号に初期値を格納する */
    pDist[i]=99999; /* 出発地から各地点までの最短距離に初期値を格納する */
    pFixed[i]=false; /* 各地点の最短距離の確定状態に初期値を格納する */
  }
  
  pDist[sp]=0;/* 出発地から出発地自体への最短距離に0を設定する */
  
  while(true){ /* 最短経路探索処理 */
    i=0;
    while(i<nPoint){/* 未確定の地点を1つ探す */
      if(pFixed[i]==0){
        break; /* 再内側の繰り返しから抜ける */
      }
      i=i+1;
    }
    
    if(i==nPoint){ /* 出発地から全ての地点までの最短経路が確定していれば */
      break; /* 最短経路探索処理を抜ける */
    }
    
    for(j=i+1;j<nPoint;j++){ /* 最短距離がより短い地点を探す */
      if((pFixed[j]==0) && (pDist[j] < pDist[i])){
        i=j;
      }
    }
    
    sPoint=i;
    pFixed[sPoint]=true; /* 出発地からの最短距離を確定する */
    
    for(j=0;j<nPoint;j++){
      if((Distance[sPoint][j]>0) && (pFixed[j]==0)){
        newDist=pDist[sPoint]+Distance[sPoint][j];
        if(newDist<pDist[j]){
          pDist[j]=newDist;
          pRoute[j]=sPoint;
        }
      }
    }
  }
  
  sDist=pDist[dp];
  j=0;
  i=dp;
  while(i!=sp){
    sRoute[j]=i;
    i=pRoute[i];
    j=j+1;
  }
  sRoute[j]=sp;
  
  /* 出力値表示 */
  printf("出発地から目的地までの最短経路\n");
  for(i=j;i>=0;i--){
    printf("%d,",sRoute[i]);
  }
  printf("\n出発地から目的地までの最短距離sDist = %d",sDist);
  
  return 0;