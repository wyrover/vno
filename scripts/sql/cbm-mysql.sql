drop table if exists account;

drop table if exists adj_layer;

drop table if exists coal;

drop table if exists complexity;

drop table if exists design_drilling_surf_technology;

drop table if exists design_eval_unit;

drop table if exists design_eval_unit_partition;

drop table if exists design_goaf_pore;

drop table if exists design_goaf_technology;

drop table if exists design_pore;

drop table if exists design_site;

drop table if exists design_technology;

drop table if exists design_tunnel_control_point;

drop table if exists design_work_surf_control_point;

drop table if exists design_work_surf_technology;

drop table if exists drilling_radius_param;

drop table if exists drilling_surf;

drop table if exists high_drilling_pore;

drop table if exists high_drilling_pore_param;

drop table if exists high_drilling_site_param;

drop table if exists high_drilling_tunnel;

drop table if exists hydr_geo;

drop table if exists mine;

drop table if exists mine_base;

drop table if exists mine_region;

drop table if exists pore_flow;

drop table if exists pore_size;

drop table if exists res_abundance;

drop table if exists rock;

drop table if exists sys_info;

drop table if exists tech_mode;

drop table if exists technology;

drop table if exists topo_geo;

drop table if exists tunnel;

drop table if exists work_area;

drop table if exists work_surf;

create table account
(
   id                   int not null auto_increment,
   username             varchar(20) not null,
   password             varchar(20) not null,
   comment              varchar(255),
   primary key (id)
);

create table adj_layer
(
   id                   int not null auto_increment,
   work_surf_id         int,
   coal_id              int,
   name                 varchar(255),
   num                  int,
   h                    decimal(8,2),
   hp                   decimal(8,2),
   in_cz                int,
   comment              varchar(255),
   primary key (id)
);

alter table adj_layer comment '回采工作面就是开采层';

create table coal
(
   id                   int not null auto_increment,
   mine_id              int,
   name                 varchar(20),
   minable              int default 1,
   thick                decimal(8,2),
   hw                   decimal(8,2),
   qa                   decimal(8,2),
   qr                   decimal(8,2),
   fore_qr              decimal(8,2),
   fore_qa              decimal(8,2),
   rank                 int,
   quality              int,
   pressure             decimal(10,2),
   gas_content          decimal(8,2),
   f_value              decimal(8,2),
   res_abundance        int,
   complexity           int,
   mine_index           decimal(8,2),
   var_coeff            decimal(8,2),
   stability            int,
   dip_angle            decimal(8,2),
   czh                  decimal(8,2),
   czk                  decimal(8,2),
   czw                  decimal(8,2),
   hw_sum               decimal(8,2),
   rock                 int,
   hhh                  decimal(8,2),
   layer_gap            decimal(8,2),
   influence_factor     decimal(8,2),
   res_a1               decimal(8,2),
   gas_x1               decimal(8,2),
   res_a2               decimal(8,2),
   gas_x2               decimal(8,2),
   pump_wc              decimal(8,2),
   pump_k               decimal(8,2),
   pump_k2              decimal(8,2),
   pump_k3              decimal(8,2),
   pump_k4              decimal(8,2),
   pump_k1              decimal(8,2),
   pore_datas           varchar(500),
   rho                  decimal(8,2),
   vr                   decimal(8,2),
   gas_w0               decimal(8,2),
   gas_wc2              decimal(8,2),
   gas_wc3              decimal(8,2),
   gas_eta              decimal(8,2),
   q0                   decimal(8,2),
   eval_method          int,
   q0_alpha             decimal(8,2),
   qt_alpha             decimal(8,2),
   t_alpha              decimal(8,2),
   q_lambda             decimal(8,2),
   r_lambda             decimal(8,2),
   p0_lambda            decimal(10,2),
   p1_lambda            decimal(10,2),
   t_lambda             decimal(8,2),
   a_lambda             decimal(8,2),
   p1_k                 decimal(10,2),
   p2_k                 decimal(10,2),
   gas_q                decimal(8,2),
   core_height          decimal(8,2),
   core_area            decimal(8,2),
   gas_viscosity        decimal(8,2),
   decay_alpha          decimal(8,2),
   permeability_lambda  decimal(8,2),
   permeability_k       decimal(8,2),
   eval_difficult       int,
   comment              varchar(255),
   primary key (id)
);

alter table coal comment '煤层基本信息参数表';

create table complexity
(
   id                   int not null,
   name                 varchar(255),
   details              varchar(255),
   comment              varchar(255),
   primary key (id)
);

create table design_drilling_surf_technology
(
   id                   int not null auto_increment,
   design_technology_id int,
   name                 varchar(255),
   comment              varchar(255),
   v_offset             decimal(8,2),
   h_offset             decimal(8,2),
   dp                   decimal(8,2),
   gp                   decimal(8,2),
   leading_dist         decimal(8,2),
   gbp                  decimal(8,2),
   l_stripe             decimal(8,2),
   ls                   decimal(8,2),
   ws                   decimal(8,2),
   hs                   decimal(8,2),
   gs                   decimal(8,2),
   wd                   decimal(8,2),
   hd                   decimal(8,2),
   l1                   decimal(8,2),
   l2                   decimal(8,2),
   w                    decimal(8,2),
   h                    decimal(8,2),
   top_side             decimal(8,2),
   bottom_side          decimal(8,2),
   left_side            decimal(8,2),
   right_side           decimal(8,2),
   lm                   decimal(8,2),
   close_length         decimal(8,2),
   primary key (id)
);

create table design_eval_unit
(
   id                   int not null auto_increment,
   design_eval_unit_partition_id int,
   name                 varchar(255),
   comment              varchar(255),
   num                  int,
   l                    decimal(8,2),
   t                    int,
   primary key (id)
);

create table design_eval_unit_partition
(
   id                   int not null auto_increment,
   work_surf_id         int,
   name                 varchar(255),
   comment              varchar(255),
   l2                   decimal(8,2),
   l1                   decimal(8,2),
   w                    decimal(8,2),
   h                    decimal(8,2),
   l                    decimal(8,2),
   r                    decimal(8,2),
   t                    decimal(8,2),
   v                    decimal(8,2),
   primary key (id)
);

create table design_goaf_pore
(
   id                   int not null auto_increment,
   design_goaf_technology_id int,
   name                 varchar(255),
   h_offset             decimal(8,2),
   v_offset             decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table design_goaf_technology
(
   id                   int not null auto_increment,
   design_technology_id int,
   name                 varchar(255),
   comment              varchar(255),
   pore_stubble         decimal(8,2),
   dp                   decimal(8,2),
   gs                   decimal(8,2),
   ls                   decimal(8,2),
   ws                   decimal(8,2),
   hs                   decimal(8,2),
   gp                   decimal(8,2),
   pore_num             int,
   top_dist             decimal(8,2),
   h_offset             varchar(255),
   y_offset             varchar(255),
   l1                   decimal(8,2),
   l2                   decimal(8,2),
   w                    decimal(8,2),
   h                    decimal(8,2),
   close_length         decimal(8,2),
   primary key (id)
);

create table design_pore
(
   id                   int not null auto_increment,
   design_eval_unit_id  int,
   design_site_id       int,
   name                 varchar(255),
   d                    decimal(8,2),
   x1                   decimal(8,2),
   y1                   decimal(8,2),
   z1                   decimal(8,2),
   x2                   decimal(8,2),
   y2                   decimal(8,2),
   z2                   decimal(8,2),
   length               decimal(8,2),
   angle1               decimal(8,2),
   angle2               decimal(8,2),
   comment              varchar(255),
   t                    int,
   primary key (id)
);

create table design_site
(
   id                   int not null auto_increment,
   design_technology_id int,
   name                 varchar(255),
   w                    decimal(8,2),
   h                    decimal(8,2),
   x                    decimal(8,2),
   y                    decimal(8,2),
   z                    decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table design_technology
(
   id                   int not null auto_increment,
   coal_id              int,
   name                 varchar(255),
   region               int,
   comment              varchar(255),
   primary key (id)
);

create table design_tunnel_control_point
(
   id                   int not null auto_increment,
   design_eval_unit_partition_id int,
   name                 varchar(255),
   comment              varchar(255),
   x                    decimal(8,2),
   y                    decimal(8,2),
   z                    decimal(8,2),
   primary key (id)
);

create table design_work_surf_control_point
(
   id                   int not null auto_increment,
   design_eval_unit_partition_id int,
   name                 varchar(255),
   comment              varchar(255),
   x                    decimal(8,2),
   y                    decimal(8,2),
   z                    decimal(8,2),
   primary key (id)
);

create table design_work_surf_technology
(
   id                   int not null auto_increment,
   design_technology_id int,
   name                 varchar(255),
   comment              varchar(255),
   top_side             decimal(8,2),
   bottom_side          decimal(8,2),
   right_side           decimal(8,2),
   l1                   decimal(8,2),
   w                    decimal(8,2),
   h                    decimal(8,2),
   l2                   decimal(8,2),
   left_side            decimal(8,2),
   v_offset             decimal(8,2),
   h_offset             decimal(8,2),
   p_offset             decimal(8,2),
   wd                   decimal(8,2),
   hd                   decimal(8,2),
   lm                   decimal(8,2),
   ws                   decimal(8,2),
   ls                   decimal(8,2),
   gs                   decimal(8,2),
   hs                   decimal(8,2),
   dp                   decimal(8,2),
   gp                   decimal(8,2),
   single_rock_tunnel   int,
   d_offset             decimal(8,2),
   pore_stubble         decimal(8,2),
   pore_angle           decimal(8,2),
   pore_type            int,
   close_length         decimal(8,2),
   primary key (id)
);

create table drilling_radius_param
(
   id                   int not null auto_increment,
   coal_id              int,
   name                 varchar(255),
   r                    decimal(8,2),
   l                    decimal(8,2),
   k1                   decimal(8,2),
   rho                  decimal(8,2),
   q0                   decimal(8,2),
   a                    decimal(8,2),
   t                    decimal(8,2),
   qm                   decimal(8,2),
   qsum                 decimal(8,2),
   eta                  decimal(8,2),
   r0                   decimal(8,2),
   p0                   decimal(8,2),
   r1                   decimal(8,2),
   primary key (id)
);

create table drilling_surf
(
   id                   int not null auto_increment,
   work_area_id         int,
   tunnel_id            int,
   name                 varchar(255),
   qr                   decimal(8,2),
   qa                   decimal(8,2),
   fore_qr              decimal(8,2),
   fore_qa              decimal(8,2),
   q4                   decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table high_drilling_pore
(
   id                   int not null auto_increment,
   high_drilling_pore_param_id int,
   num                  int,
   length               decimal(8,2),
   angle                decimal(8,2),
   pore_type            int,
   comment              varchar(255),
   primary key (id)
);

create table high_drilling_pore_param
(
   id                   int not null auto_increment,
   work_surf_id         int,
   name                 varchar(255),
   lk                   decimal(8,2),
   lc                   decimal(8,2),
   lw                   decimal(8,2),
   n1                   int,
   n2                   int,
   beta                 decimal(8,2),
   ld                   decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table high_drilling_site_param
(
   id                   int not null auto_increment,
   work_surf_id         int,
   name                 varchar(255),
   l1                   decimal(8,2),
   l2                   decimal(8,2),
   lg                   decimal(8,2),
   hn                   decimal(8,2),
   theta                decimal(8,2),
   q                    decimal(8,2),
   rtn                  decimal(8,2),
   hs                   decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table high_drilling_tunnel
(
   id                   int not null auto_increment,
   work_surf_id         int,
   name                 varchar(255),
   k                    decimal(8,2),
   rock                 int,
   hz_min               decimal(8,2),
   hz_max               decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table hydr_geo
(
   id                   int not null,
   name                 varchar(20),
   x1                   int,
   x2                   int,
   x3                   int,
   x4                   decimal(8,2),
   x5                   decimal(8,2),
   x6                   decimal(8,2),
   x7                   decimal(8,2),
   x8                   varchar(255),
   primary key (id)
);

create table mine
(
   id                   int not null auto_increment,
   tech_mode_id         int,
   mine_region_id       int,
   account_id           int,
   name                 varchar(255),
   province             varchar(20),
   city                 varchar(20),
   capacity             decimal(8,2),
   topo_geo             int,
   hydr_geo             int,
   ground_condition     int,
   qr                   decimal(8,2),
   qa                   decimal(8,2),
   fore_qr              decimal(8,2),
   fore_qa              decimal(8,2),
   gas_k1               decimal(8,2),
   gas_k2               decimal(8,2),
   stereo_schem_diagram varchar(255),
   rock_gas_k2          decimal(8,2),
   protect_layer_condition int,
   reserve_w1           decimal(8,2),
   reserve_w2           decimal(8,2),
   reserve_w3           decimal(8,2),
   gas_w0               decimal(8,2),
   gas_wc2              decimal(8,2),
   pump_k2              decimal(8,2),
   pump_k3              decimal(8,2),
   pump_k4              decimal(8,2),
   pump_k1              decimal(8,2),
   pump_k               decimal(8,2),
   pump_wc              decimal(8,2),
   reserve_gas          decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

alter table mine comment '账户管理数据表（包括矿井的基本信息）';

create table mine_base
(
   id                   int not null,
   name                 varchar(50),
   comment              varchar(255),
   primary key (id)
);

alter table mine_base comment '这个只是一个帮助下拉列表，类似于省市县这种3联动菜单，见文档的P8 3.1';

create table mine_region
(
   id                   int not null,
   mine_base_id         int,
   name                 varchar(20),
   comment              varchar(255),
   primary key (id)
);

create table pore_flow
(
   id                   int not null auto_increment,
   name                 varchar(255),
   t                    decimal(8,2),
   a0                   decimal(8,2),
   d                    decimal(8,2),
   d1                   decimal(8,2),
   m                    decimal(8,2),
   k                    decimal(8,2),
   delta_t              decimal(8,2),
   x                    decimal(8,2),
   p_test               decimal(8,2),
   p_cur                decimal(8,2),
   b                    decimal(8,2),
   pt                   decimal(8,2),
   delta_p              decimal(8,2),
   dh                   decimal(8,2),
   q_hun                decimal(8,2),
   q_chun               decimal(8,2),
   primary key (id)
);

create table pore_size
(
   id                   int not null auto_increment,
   name                 varchar(255),
   q                    decimal(8,2),
   v                    decimal(8,2),
   d                    decimal(8,2),
   p                    decimal(8,2),
   sigma                decimal(8,2),
   delta                decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table res_abundance
(
   id                   int not null,
   name                 varchar(20),
   min_abundance        decimal(8,2),
   max_abundance        decimal(8,2),
   primary key (id)
);

create table rock
(
   id                   int not null,
   name                 varchar(50),
   a                    decimal(3,1),
   b                    decimal(3,1),
   c                    decimal(3,1),
   comment              varchar(255),
   primary key (id)
);

create table sys_info
(
   id                   int not null auto_increment,
   account_id           int,
   last_login_time      varchar(255),
   comment              varchar(255),
   primary key (id)
);

alter table sys_info comment '记录当前的一些信息，比如当前用户';

create table tech_mode
(
   id                   int not null,
   mine_region_id       int,
   name                 varchar(255),
   mode_type            int,
   c1                   int,
   c2                   int,
   c3                   int,
   comment              varchar(255),
   primary key (id)
);

create table technology
(
   id                   int not null,
   mine_region_id       int,
   name                 varchar(255),
   iskey                int,
   doc                  varchar(255),
   video                varchar(255),
   comment              varchar(255),
   primary key (id)
);

create table topo_geo
(
   id                   int not null,
   name                 varchar(20),
   feature              varchar(255),
   comment              varchar(255),
   primary key (id)
);

create table tunnel
(
   id                   int not null auto_increment,
   name                 varchar(255),
   b                    decimal(8,2),
   h                    decimal(8,2),
   l                    decimal(8,2),
   s                    decimal(8,2),
   d                    decimal(8,2),
   wh                   decimal(8,2),
   v                    decimal(8,2),
   q3                   decimal(8,2),
   q0                   decimal(8,2),
   comment              varchar(255),
   tunnel_type          int,
   top_side             decimal(8,2),
   bottom_side          decimal(8,2),
   left_side            decimal(8,2),
   right_side           decimal(8,2),
   x1                   decimal(8,2),
   y1                   decimal(8,2),
   z1                   decimal(8,2),
   x2                   decimal(8,2),
   y2                   decimal(8,2),
   z2                   decimal(8,2),
   primary key (id)
);

alter table tunnel comment '所有的巷道列表';

create table work_area
(
   id                   int not null auto_increment,
   coal_id              int,
   name                 varchar(255),
   mode                 int default 1,
   a                    decimal(8,2),
   qr                   decimal(8,2),
   qa                   decimal(8,2),
   fore_qr              decimal(8,2),
   fore_qa              decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

create table work_surf
(
   id                   int not null auto_increment,
   work_area_id         int,
   tunnel_id            int,
   name                 varchar(255),
   a                    decimal(8,2),
   qr                   decimal(8,2),
   qa                   decimal(8,2),
   fore_qr              decimal(8,2),
   fore_qa              decimal(8,2),
   l1                   decimal(8,2),
   l2                   decimal(8,2),
   layerable            int,
   k1                   decimal(8,2),
   k2                   decimal(8,2),
   k3                   decimal(8,2),
   kf                   decimal(8,2),
   method               int,
   last_t               decimal(8,2),
   qr1                  decimal(8,2),
   qr2                  decimal(8,2),
   comment              varchar(255),
   primary key (id)
);

alter table adj_layer add constraint fk_relationship_16 foreign key (work_surf_id)
      references work_surf (id) on delete cascade on update restrict;

alter table adj_layer add constraint fk_relationship_32 foreign key (coal_id)
      references coal (id) on delete cascade on update restrict;

alter table coal add constraint fk_relationship_1 foreign key (mine_id)
      references mine (id) on delete cascade on update restrict;

alter table design_drilling_surf_technology add constraint fk_relationship_31 foreign key (design_technology_id)
      references design_technology (id) on delete cascade on update restrict;

alter table design_eval_unit add constraint fk_relationship_42 foreign key (design_eval_unit_partition_id)
      references design_eval_unit_partition (id) on delete cascade on update restrict;

alter table design_eval_unit_partition add constraint fk_relationship_44 foreign key (work_surf_id)
      references work_surf (id) on delete cascade on update restrict;

alter table design_goaf_pore add constraint fk_relationship_45 foreign key (design_goaf_technology_id)
      references design_goaf_technology (id) on delete cascade on update restrict;

alter table design_goaf_technology add constraint fk_relationship_39 foreign key (design_technology_id)
      references design_technology (id) on delete cascade on update restrict;

alter table design_pore add constraint fk_relationship_38 foreign key (design_site_id)
      references design_site (id) on delete cascade on update restrict;

alter table design_pore add constraint fk_relationship_43 foreign key (design_eval_unit_id)
      references design_eval_unit (id) on delete cascade on update restrict;

alter table design_site add constraint fk_relationship_36 foreign key (design_technology_id)
      references design_technology (id) on delete cascade on update restrict;

alter table design_technology add constraint fk_relationship_35 foreign key (coal_id)
      references coal (id) on delete cascade on update restrict;

alter table design_tunnel_control_point add constraint fk_relationship_40 foreign key (design_eval_unit_partition_id)
      references design_eval_unit_partition (id) on delete cascade on update restrict;

alter table design_work_surf_control_point add constraint fk_relationship_41 foreign key (design_eval_unit_partition_id)
      references design_eval_unit_partition (id) on delete cascade on update restrict;

alter table design_work_surf_technology add constraint fk_relationship_37 foreign key (design_technology_id)
      references design_technology (id) on delete cascade on update restrict;

alter table drilling_radius_param add constraint fk_relationship_12 foreign key (coal_id)
      references coal (id) on delete cascade on update restrict;

alter table drilling_surf add constraint fk_relationship_22 foreign key (tunnel_id)
      references tunnel (id) on delete cascade on update restrict;

alter table drilling_surf add constraint fk_relationship_27 foreign key (work_area_id)
      references work_area (id) on delete cascade on update restrict;

alter table high_drilling_pore add constraint fk_relationship_34 foreign key (high_drilling_pore_param_id)
      references high_drilling_pore_param (id) on delete cascade on update restrict;

alter table high_drilling_pore_param add constraint fk_relationship_33 foreign key (work_surf_id)
      references work_surf (id) on delete cascade on update restrict;

alter table high_drilling_site_param add constraint fk_relationship_11 foreign key (work_surf_id)
      references work_surf (id) on delete cascade on update restrict;

alter table high_drilling_tunnel add constraint fk_relationship_5 foreign key (work_surf_id)
      references work_surf (id) on delete cascade on update restrict;

alter table mine add constraint fk_relationship_19 foreign key (mine_region_id)
      references mine_region (id) on delete cascade on update restrict;

alter table mine add constraint fk_relationship_28 foreign key (account_id)
      references account (id) on delete cascade on update restrict;

alter table mine add constraint fk_relationship_30 foreign key (tech_mode_id)
      references tech_mode (id) on delete cascade on update restrict;

alter table mine_region add constraint fk_relationship_23 foreign key (mine_base_id)
      references mine_base (id) on delete cascade on update restrict;

alter table sys_info add constraint fk_relationship_29 foreign key (account_id)
      references account (id) on delete cascade on update restrict;

alter table tech_mode add constraint fk_relationship_25 foreign key (mine_region_id)
      references mine_region (id) on delete cascade on update restrict;

alter table technology add constraint fk_relationship_24 foreign key (mine_region_id)
      references mine_region (id) on delete cascade on update restrict;

alter table work_area add constraint fk_relationship_9 foreign key (coal_id)
      references coal (id) on delete cascade on update restrict;

alter table work_surf add constraint fk_relationship_21 foreign key (tunnel_id)
      references tunnel (id) on delete cascade on update restrict;

alter table work_surf add constraint fk_relationship_26 foreign key (work_area_id)
      references work_area (id) on delete cascade on update restrict;

