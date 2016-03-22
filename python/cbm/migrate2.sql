drop table if exists design_goaf_technology;

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

alter table design_goaf_technology add constraint fk_relationship_39 foreign key (design_technology_id)
      references design_technology (id) on delete cascade on update restrict;

drop table if exists design_goaf_pore;

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

alter table design_goaf_pore add constraint fk_relationship_45 foreign key (design_goaf_technology_id)
      references design_goaf_technology (id) on delete cascade on update restrict;